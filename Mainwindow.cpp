#include "Mainwindow.h"
#include "ui_Mainwindow.h"

QMediaPlaylist* loadingBGMList = new (QMediaPlaylist);//loading->start��bgm
QMediaPlayer* loadingBGM = new (QMediaPlayer);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadingBGMList->addMedia(QUrl::fromLocalFile("./sound/02CrazyDave.mp3"));
    // ��׽QMediaPlayer�Ĵ����ź�
    loadingBGMList->setPlaybackMode(QMediaPlaylist::Loop);
    loadingBGM->setPlaylist(loadingBGMList);
    loadingBGM->setVolume(musicVolume);
    loadingBGM->play();
    ui->setupUi(this);
    this->setFixedSize(900,600);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // ���ô���ͼ��
    mpainter_1 = new QPainter(this); // ���� QPainter ����
    mqtimer = new QTimer(this); // ���� QTimer ����
    mqtimer->setInterval(4000); // ���ö�ʱ��ʱ����Ϊ 4000 ����
    mqtimer->start(); // ������ʱ��
    connect(mqtimer, &QTimer::timeout, [this]() {
        loading* load = new(loading);
        mqtimer->stop(); // ��ʱ��������ֹͣ
        this->close(); // �ر�������
        load->show(); // ��ʾ loading ����
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // ��ʼ����
    QImage img(":/new/prefix1/init.png"); // ����ͼƬ��Դ
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // �������ڻ���ͼƬ
    mpainter_1->end(); // ��������
}




