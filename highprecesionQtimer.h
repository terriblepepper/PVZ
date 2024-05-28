// highPrecisionTimer.h
#ifndef HIGHPRECISIONTIMER_H
#define HIGHPRECISIONTIMER_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimerEvent>

class HighPrecisionTimer : public QObject {
    Q_OBJECT

public:
    explicit HighPrecisionTimer(QObject* parent = nullptr);
    void start(int msec);
    void stop();
    void pause(); 
    void resume();
signals:
    void timeout();

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    QElapsedTimer timer;
    qint64 nextTrigger;
    int interval;
    bool running;
    int timerId;
    qint64 pausedTime; // 保存暂停时的时间点
};

#endif // HIGHPRECISIONTIMER_H
