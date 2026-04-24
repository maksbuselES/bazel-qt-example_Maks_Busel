#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QProgressBar>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include "session_engine.h"
#include "exercises.h"
#include "task_repository.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    QStackedWidget* stack;
    QProgressBar* progress;
    QLabel* infoLabel;
    QLabel* feedbackToast;
    
    QSpinBox *timeSpin, *livesSpin;
    QCheckBox* typoCheck;
    QComboBox* diffCombo;
    QPushButton* skipBtn; // Кнопка пропуска

    SessionEngine* engine;
    int currentTaskIndex = 0;

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void startGame(TaskType type);
    void handleSubmit();
    void handleSkip(); // Тот самый пропуск
    void updateUI();
    void returnToMenu();
    void showFeedback(bool correct);
    void onSessionFinished(bool success, QString msg);
    void openDifficultyDialog();
    void showRules();
};