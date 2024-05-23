#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include<QString>
//#include <QtMultimedia>
//#include <QMediaPlayer>
//#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//extern QMediaPlaylist* loadingBGMList;
//extern QMediaPlayer* loadingBGM;

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

};
#endif // MAINWINDOW_H
