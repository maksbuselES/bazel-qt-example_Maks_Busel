#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include "fuzzy_matcher.h"

class IExercise : public QWidget {
    Q_OBJECT
public:
    explicit IExercise(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual bool check(bool allowTypo) = 0;
    virtual QString getHint() = 0;
};

// ПУНКТ 4 ТЗ: PushButton + TextEdit (Translation)
class TranslationTask : public IExercise {
    Q_OBJECT
    QLineEdit* input;
    QString target;
public:
    TranslationTask(QString q, QString a, QWidget* parent = nullptr) : IExercise(parent), target(a) {
        auto* l = new QVBoxLayout(this);
        l->addWidget(new QLabel("👉 Переведите слово: " + q));
        input = new QLineEdit();
        l->addWidget(input);
        auto* sub = new QPushButton("Submit Translation");
        connect(sub, &QPushButton::clicked, [this](){ QMetaObject::invokeMethod(window(), "handleSubmit"); });
        l->addWidget(sub);
        l->addStretch();
    }
    bool check(bool typo) override {
        int d = utils::levenshtein(input->text().trimmed().toLower(), target.toLower());
        return typo ? d <= 1 : d == 0;
    }
    QString getHint() override { return "Ответ начинается на букву: " + target.left(1); }
};

// ПУНКТ 5 ТЗ: PushButton + RadioBox (Grammar)
class GrammarTask : public IExercise {
    Q_OBJECT
    QButtonGroup* group;
    int correctIdx;
public:
    GrammarTask(QString q, QStringList opts, int correct, QWidget* parent = nullptr) : IExercise(parent), correctIdx(correct) {
        auto* l = new QVBoxLayout(this);
        l->addWidget(new QLabel("👉 Выберите правильный вариант: " + q));
        group = new QButtonGroup(this);
        for(int i=0; i<opts.size(); ++i) {
            auto* rb = new QRadioButton(opts[i]);
            group->addButton(rb, i);
            l->addWidget(rb);
        }
        auto* sub = new QPushButton("Submit Grammar");
        connect(sub, &QPushButton::clicked, [this](){ QMetaObject::invokeMethod(window(), "handleSubmit"); });
        l->addWidget(sub);
        l->addStretch();
    }
    bool check(bool) override { return group->checkedId() == correctIdx; }
    QString getHint() override { return "Это грамматика, подумайте над формой глагола."; }
};