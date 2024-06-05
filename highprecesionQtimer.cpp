#include"highprecesionQtimer.h"
#include <QDebug>

TimerThread::TimerThread(QObject* parent)
    : QThread(parent), mRunning(false), mPaused(false), mIntervalUs(33333 / fpsIndex)
{
}

TimerThread::~TimerThread()
{
    stop();
    wait();  // 确保线程已退出
}

void TimerThread::run()
{
    mRunning = true;
    mTimer.start();
    qint64 nextWakeup = mTimer.nsecsElapsed() + mIntervalUs * 1000;

    while (mRunning) 
    {
        {
            QMutexLocker locker(&mMutex);
            if (mPaused) {
                mCondition.wait(&mMutex);  // 等待恢复
            }
        }
        emit timeout();
        qint64 sleepTime = nextWakeup - mTimer.nsecsElapsed();
        if (sleepTime > 0) {
            QThread::usleep(sleepTime / 1000);
        }
        nextWakeup += mIntervalUs * 1000;
    }
}

void TimerThread::pause()
{
    QMutexLocker locker(&mMutex);
    mPaused = true;
}

void TimerThread::resume()
{
    {
        QMutexLocker locker(&mMutex);
        mPaused = false;
    }
    mCondition.wakeAll();  // 唤醒暂停的线程
}

void TimerThread::stop()
{
    mRunning = false;
    {
        QMutexLocker locker(&mMutex);
        mPaused = false;
    }
    mCondition.wakeAll();  // 确保线程不会在暂停状态卡住
    quit();  // 退出事件循环
    wait();
}
