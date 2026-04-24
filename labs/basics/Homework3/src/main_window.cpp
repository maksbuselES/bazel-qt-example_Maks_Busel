#include "main_window.h"
#include "style.h"
#include "task_repository.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QApplication>
#include <algorithm>
#include <random>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setStyleSheet(styles::MAIN_STYLE);
    this->setMinimumSize(700, 650);

    auto* central = new QWidget();
    auto* mainLayout = new QVBoxLayout(central);
    setCentralWidget(central);

    // --- MENU BAR (Пункт 3 ТЗ) ---
    auto* mMenu = menuBar()->addMenu("Меню");
    mMenu->addAction("Инструкция", this, &MainWindow::showRules);
    mMenu->addAction("Настройки сложности", this, &MainWindow::openDifficultyDialog);
    mMenu->addAction("В главное меню", this, &MainWindow::returnToMenu);

    progress = new QProgressBar(); progress->hide();
    infoLabel = new QLabel("Language Master PRO");
    mainLayout->addWidget(progress);
    mainLayout->addWidget(infoLabel, 0, Qt::AlignCenter);

    stack = new QStackedWidget();
    mainLayout->addWidget(stack);

    feedbackToast = new QLabel(this);
    feedbackToast->setAlignment(Qt::AlignCenter);
    feedbackToast->setFixedSize(300, 80);
    feedbackToast->hide();

    // --- ГЛАВНЫЙ ЭКРАН ---
    auto* menuPage = new QWidget();
    auto* mLayout = new QVBoxLayout(menuPage);
    auto* title = new QLabel("🌍 Выберите категорию 🌍");
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #58CC02;");

    auto* settingsForm = new QWidget();
    auto* formLayout = new QVBoxLayout(settingsForm);
    
    formLayout->addWidget(new QLabel("Сложность:"));
    diffCombo = new QComboBox(); diffCombo->addItems({"Легко", "Средне", "Сложно"});
    formLayout->addWidget(diffCombo);

    formLayout->addWidget(new QLabel("Время на сессию:"));
    timeSpin = new QSpinBox(); timeSpin->setRange(20, 300); timeSpin->setValue(90);
    formLayout->addWidget(timeSpin);

    formLayout->addWidget(new QLabel("Жизни (M ошибок):"));
    livesSpin = new QSpinBox(); livesSpin->setRange(1, 10); livesSpin->setValue(3);
    formLayout->addWidget(livesSpin);

    typoCheck = new QCheckBox("Допускать опечатку (Translation)");
    formLayout->addWidget(typoCheck);

    // Пункты 4 и 5 ТЗ: Кнопки старта
    auto* btnTrans = new QPushButton("Translation Mode");
    auto* btnGram = new QPushButton("Grammar Mode");
    btnGram->setObjectName("secondary");

    connect(btnTrans, &QPushButton::clicked, [this](){ startGame(TaskType::Translation); });
    connect(btnGram, &QPushButton::clicked, [this](){ startGame(TaskType::Grammar); });

    mLayout->addStretch();
    mLayout->addWidget(title, 0, Qt::AlignCenter);
    mLayout->addWidget(settingsForm);
    mLayout->addWidget(btnTrans);
    mLayout->addWidget(btnGram);
    mLayout->addStretch();
    stack->addWidget(menuPage);

    // Кнопка ПРОПУСКА (будет видна только в игре)
    skipBtn = new QPushButton("ПРОПУСТИТЬ ЗА 1 ❤");
    skipBtn->setObjectName("secondary");
    skipBtn->hide();
    connect(skipBtn, &QPushButton::clicked, this, &MainWindow::handleSkip);
    mainLayout->addWidget(skipBtn);

    engine = new SessionEngine(this);
    connect(engine, &SessionEngine::tick, this, &MainWindow::updateUI);
    connect(engine, &SessionEngine::finished, this, &MainWindow::onSessionFinished);

    qApp->installEventFilter(this);
}

void MainWindow::startGame(TaskType type) {
    while (stack->count() > 1) {
        auto* w = stack->widget(1);
        stack->removeWidget(w);
        delete w;
    }

    auto all = TaskRepository::getAllTasks();
    std::vector<TaskData> filtered;
    Difficulty d = (Difficulty)diffCombo->currentIndex();
    for(const auto& t : all) if(t.diff == d && t.type == type) filtered.push_back(t);

    std::random_device rd; std::mt19937 g(rd());
    std::shuffle(filtered.begin(), filtered.end(), g);

    int n = std::min((int)filtered.size(), 5);
    for(int i=0; i < n; ++i) {
        if(type == TaskType::Translation)
            stack->addWidget(new TranslationTask(filtered[i].question, filtered[i].answer, this));
        else
            stack->addWidget(new GrammarTask(filtered[i].question, filtered[i].options, filtered[i].answer.toInt(), this));
    }

    currentTaskIndex = 1;
    stack->setCurrentIndex(1);
    progress->show(); progress->setRange(0, n); progress->setValue(0);
    skipBtn->show(); // Показываем пропуск
    
    engine->startSession(timeSpin->value(), livesSpin->value());
    updateUI();
}

void MainWindow::handleSubmit() {
    IExercise* task = qobject_cast<IExercise*>(stack->currentWidget());
    if (task) {
        bool correct = task->check(typoCheck->isChecked());
        showFeedback(correct);
        engine->submit(correct);
        if (correct) {
            currentTaskIndex++;
            progress->setValue(currentTaskIndex - 1);
            if (currentTaskIndex < stack->count()) stack->setCurrentIndex(currentTaskIndex);
            else onSessionFinished(true, "Урок завершен!");
        }
    }
    updateUI();
}

void MainWindow::handleSkip() {
    engine->submit(false); // Тратим жизнь
    currentTaskIndex++;
    progress->setValue(currentTaskIndex - 1);
    if (currentTaskIndex < stack->count()) {
        stack->setCurrentIndex(currentTaskIndex);
    } else {
        onSessionFinished(true, "Урок завершен с пропусками.");
    }
    updateUI();
}

void MainWindow::updateUI() {
    QString h = "";
    int l = engine->getMaxMistakes() - engine->getMistakes();
    for(int i=0; i<l; ++i) h += "❤ ";
    infoLabel->setText(QString("%1 | %2с").arg(h).arg(engine->getTime()));
}

void MainWindow::showFeedback(bool correct) {
    feedbackToast->setText(correct ? "ВЕРНО!" : "ОШИБКА!");
    feedbackToast->setStyleSheet(correct ? styles::TOAST_CORRECT : styles::TOAST_WRONG);
    feedbackToast->move((width()-300)/2, (height()-80)/2);
    feedbackToast->show();
    QTimer::singleShot(800, feedbackToast, &QLabel::hide);
}

void MainWindow::onSessionFinished(bool success, QString msg) {
    engine->stop();
    int score = success ? engine->getScore() : 0;
    QMessageBox::information(this, "Финал", msg + "\nБаллы: " + QString::number(score));
    returnToMenu();
}

void MainWindow::returnToMenu() {
    engine->stop();
    stack->setCurrentIndex(0);
    progress->hide();
    skipBtn->hide();
    infoLabel->setText("Language Master PRO");
}

void MainWindow::openDifficultyDialog() {
    QMessageBox::information(this, "Сложность", "Настройте параметры в главном меню.");
}

void MainWindow::showRules() {
    QMessageBox::information(this, "Инструкция", "H - подсказка. Enter - подтвердить. Пропуск стоит 1 жизнь.");
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter) {
            if (stack->currentIndex() > 0) handleSubmit(); else startGame(TaskType::Translation);
            return true;
        }
        if (ke->key() == Qt::Key_H && stack->currentIndex() > 0) {
            auto* t = qobject_cast<IExercise*>(stack->currentWidget());
            if(t) QMessageBox::information(this, "Hint", t->getHint());
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}