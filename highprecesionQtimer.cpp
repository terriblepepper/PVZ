#include "highprecesionQtimer.h"

HighPrecisionTimer::HighPrecisionTimer(QObject* parent) : QObject(parent), interval(0), running(false) {}

void HighPrecisionTimer::start(int msec) {
    interval = msec;
    running = true;
    timer.start();
    nextTrigger = timer.nsecsElapsed() / 1000 + interval;
    this->startTimer(0);
}

void HighPrecisionTimer::stop() {
    running = false;
    this->killTimer(timerId);
}

void HighPrecisionTimer::pause() {
    running = false;
    pausedTime = timer.nsecsElapsed(); // 保存暂停时的时间点
}

void HighPrecisionTimer::resume() {
    if (!running) {
        running = true;
        qint64 elapsed = timer.nsecsElapsed() - pausedTime;
        nextTrigger += elapsed / 1000; // 根据暂停的时间调整下一次触发的时间
        this->startTimer(0);
    }
}

void HighPrecisionTimer::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    if (!running) {
        return;
    }
    qint64 currentTime = timer.nsecsElapsed() / 1000;
    if (currentTime >= nextTrigger) {
        emit timeout();
        nextTrigger += interval;
    }
}
