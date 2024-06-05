#pragma once
#include <QThread>
#include <QElapsedTimer>
#include <QWaitCondition>
#include <QMutex>
#include "gameIndex.h"

class TimerThread : public QThread
{
    Q_OBJECT

public:
    explicit TimerThread(QObject* parent = nullptr);
    ~TimerThread();
    void pause();
    void resume();
    void stop();

signals:
    void timeout();

protected:
    void run() override;

private:
    QElapsedTimer mTimer;
    QWaitCondition mCondition;
    QMutex mMutex;
    bool mRunning;
    bool mPaused;
    int mIntervalUs;  // Œ¢√Îº∂º‰∏Ù
};
