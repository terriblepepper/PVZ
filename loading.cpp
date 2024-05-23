#include <QIcon>
#include <QPushButton>
#include "loading.h"
#include"startpage.h"
#include"HelpWidget.h"
loading::loading(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(900,600);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // ���ô���ͼ��
    mpainter_1 = new QPainter; // ���� QPainter ����
    QPixmap img(":/new/prefix1/floor.png"); // ����ͼƬ��Դ
    QPushButton *btn = new QPushButton(this); // ���� QPushButton ����
    btn->setGeometry(237, 433, 450, 115); // ���ð�ťλ�úʹ�С
    btn->setStyleSheet("QPushButton {"
                       "border-image: url(:/new/prefix1/floor.png) center center no-repeat;" // ���ð�ť��ʽ����������ͼƬ
                       "font-size: 32px;" // ���������С
                       "color: white;" // ����������ɫ
                       "padding-top: 40px;" // �������־��밴ť�����ľ���
                       "font - family: 'Microsoft YaHei UI'"//��������
                       "}"
                       "QPushButton:hover {" // �����ͣ��ʽ
                       "color: yellow;" // ���������ͣʱ��������ɫ
                       "}"
                       "QPushButton:pressed {" // ��ť������ʽ
                       "color: purple;" // ���ð�ť����ʱ��������ɫ
                       "}");
    btn->setText(QString("��ʼ��Ϸ��")); // ���ð�ť�ı�
        connect(btn, &QPushButton::clicked,this,&loading::startGame);

}

void loading::startGame()
{
    mstartpage = new(startpage);
    helpPage = new(HelpWidget);//������ʼ�˵��Ͱ����˵�
    mstartpage->setWidget(helpPage);
    helpPage->setWidget(mstartpage);
    this->close();//�رռ��ش���
    mstartpage->show();
}
void loading::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // ��ʼ����
    QImage img(":/new/prefix1/StartScreen.jpg"); // ����ͼƬ��Դ
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // �������ڻ���ͼƬ
    mpainter_1->drawImage(QRect(123, 20, 555, 115), QImage(":/new/prefix1/LogoWord.jpg"), QRect(0, 0, 555, 115)); // ����ͼƬ��ָ��λ�úʹ�С
    mpainter_1->end(); // ��������
}

