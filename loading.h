#ifndef LOADING_H
#define LOADING_H
#include <QWidget>
#include <QTimer>
#include <QPainter>

class startpage;
class HelpWidget;
class loading : public QWidget
{
    Q_OBJECT
public:
    QTimer* mqtimer;
    QPainter* mpainter_1;
    startpage* mstartpage;
    HelpWidget* helpPage;
    void paintEvent(QPaintEvent *event);
    explicit loading(QWidget *parent = nullptr);
   
public slots:
    void startGame();
};

#endif // LOADING_H
