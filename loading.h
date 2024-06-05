#ifndef LOADING_H
#define LOADING_H
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QIcon>
#include <QPushButton>
#include"startpage.h"
#include"HelpWidget.h"
class startpage;
class HelpWidget;
class loading : public QWidget
{
    Q_OBJECT
public:
    QPainter* mpainter_1;
    startpage* mstartpage;//开始菜单
    HelpWidget* helpPage;//帮助菜单
    void paintEvent(QPaintEvent *event);
    explicit loading(QWidget *parent = nullptr);
public slots:
    void startGame();
};

#endif // LOADING_H
