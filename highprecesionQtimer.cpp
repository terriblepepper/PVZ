#include"highprecesionQtimer.h"
#include <QDebug>

TimerThread::TimerThread(QObject* parent)
    : QThread(parent), mRunning(false), mPaused(false), mIntervalUs(33333 / fpsIndex)
{
}

TimerThread::~TimerThread()
{
    stop();
    wait();  // ȷ���߳����˳�
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
                mCondition.wait(&mMutex);  // �ȴ��ָ�
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
    mCondition.wakeAll();  // ������ͣ���߳�
}

void TimerThread::stop()
{
    mRunning = false;
    {
        QMutexLocker locker(&mMutex);
        mPaused = false;
    }
    mCondition.wakeAll();  // ȷ���̲߳�������ͣ״̬��ס
    quit();  // �˳��¼�ѭ��
    wait();
}
