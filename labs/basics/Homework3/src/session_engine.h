#pragma once
#include <QObject>
#include <QTimer>

class SessionEngine : public QObject {
    Q_OBJECT
    int score = 0;
    int mistakes = 0;
    int maxMistakes = 3;
    int timeLeft = 60;
    QTimer* timer;

public:
    explicit SessionEngine(QObject* parent = nullptr);
    
    void startSession(int seconds, int lives);
    void stop();
    void submit(bool correct);
    
    int getScore() const { return score; }
    int getMistakes() const { return mistakes; }
    int getMaxMistakes() const { return maxMistakes; }
    int getTime() const { return timeLeft; }

signals:
    void tick();
    void finished(bool success, QString msg);

private slots:
    void onTimeout();
};
