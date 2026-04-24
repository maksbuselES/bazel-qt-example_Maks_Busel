#include "session_engine.h"

SessionEngine::SessionEngine(QObject* parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SessionEngine::onTimeout);
}

void SessionEngine::startSession(int seconds, int lives) {
    score = 0;
    mistakes = 0;
    timeLeft = seconds;
    maxMistakes = lives;
    timer->start(1000);
}

void SessionEngine::stop() {
    timer->stop();
}

void SessionEngine::submit(bool correct) {
    if (correct) {
        score += 10;
    } else {
        mistakes++;
    }

    if (mistakes >= maxMistakes) {
        stop();
        emit finished(false, "У вас закончились жизни!");
    }
}

void SessionEngine::onTimeout() {
    if (timeLeft > 0) {
        timeLeft--;
        emit tick();
    } else {
        stop();
        emit finished(false, "Время вышло!");
    }
}