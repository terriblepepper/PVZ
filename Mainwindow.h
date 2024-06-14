//utf8
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include<QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "loading.h"
#include"gamingMenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class loading;
class startpage;

extern QMediaPlaylist* loadingBGMList;
extern QMediaPlayer* loadingBGM;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* mqtimer;
    QPainter* mpainter_1;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    startpage* getstartpage;
};
#endif // MAINWINDOW_H
