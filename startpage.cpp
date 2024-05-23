#include <QIcon>
#include<qmessagebox.h>
#include <QPushButton>
#include "startpage.h"
#include "game.h"
#include"gameIndex.h"
#include"Mainwindow.h"//bgm
#include "HelpWidget.h"
#include"card.h"
startpage::startpage(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(900,600);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png"));
    this->initSettings();//��ʼ����������
    mpainter_1=new QPainter(this);
    QPushButton* btn_adventure=new QPushButton(this);
    QPushButton* btn_smallgame=new QPushButton(this);
    QPushButton* btn_yizhigame=new QPushButton(this);
    QPushButton* btn_minigame=new QPushButton(this);
    QPushButton* btn_options=new QPushButton(this);
    QPushButton* btn_help = new QPushButton(this);
    QPushButton* btn_exit = new QPushButton(this);
    btn_options->setGeometry(644, 490, 72, 30);
    btn_options->setStyleSheet("QPushButton{"
                         "border:none;" // �����ޱ߿�
                         "padding:0px;" // �������ڱ߾�
                         "background:transparent;" // ���ñ���͸��        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-options.png);" // �����ͣ��ʽ 
                         "}");
    btn_help->setGeometry(728, 521, 59, 29);
    btn_help->setStyleSheet("QPushButton{"
                         "border:none;" // �����ޱ߿�
                         "padding:0px;" // �������ڱ߾�
                         "background:transparent;" // ���ñ���͸��        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-help.png);" // �����ͣ��ʽ 
                         "}");
    btn_exit->setGeometry(811, 510, 60, 30);
    btn_exit->setStyleSheet("QPushButton{"
                         "border:none;" // �����ޱ߿�
                         "padding:0px;" // �������ڱ߾�
                         "background:transparent;" // ���ñ���͸��        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-exit.png);" // �����ͣ��ʽ 
                         "}");
    btn_adventure->setGeometry(450,60,340,120);
    btn_adventure->setStyleSheet("QPushButton{"
                         "border:none;" // �����ޱ߿�
                         "padding:0px;" // �������ڱ߾�
                         "background:transparent;" // ���ñ���͸��
                         "border-image:url(:/new/prefix1/mx1.png);" // ���ð�ť��ʽ����������ͼƬ
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/mx.png);" // �����ͣ��ʽ
                         "}"
                         );
    btn_smallgame->setGeometry(450,150,320,130);
    btn_smallgame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/play1.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/play.png);"
                         "}"
                         );
    btn_yizhigame->setGeometry(460,230,290,130);
    btn_yizhigame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/yizi1.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/yizi.png);"
                         "}"
                         );
    btn_minigame->setGeometry(460,320,280,120);
    btn_minigame->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/mini1.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/mini.png);"
                         "}"
                         );

     // ����ð��
    connect(btn_adventure,&QPushButton::clicked,[this](){
        /*���ÿ�Ƭ��ȴʱ�䣨��card.cpp���û���ָ�ֵʧЧ��*/
        card::cool = { 227 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex };
        //loadingBGM->stop();
        game* ga=new game;
        this->setEnabled(false);
        this->close();
        ga->show();
    });
    //�˳�
    connect(btn_exit, &QPushButton::clicked, [this]() {
        QMessageBox exitBox;
        exitBox.setWindowTitle("�˳�");
        exitBox.setText("�Ƿ�Ҫ�˳���Ϸ?");
        exitBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        exitBox.setDefaultButton(QMessageBox::No);
        int ret = exitBox.exec();

        switch (ret) {
        case QMessageBox::Yes:
            exit(1);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
        });
    //����
    connect(btn_help, &QPushButton::clicked,this,&startpage::goToHelp);
    //����
    connect(btn_options, &QPushButton::clicked, this, &startpage::openSettingsDialog); 
}

void startpage::setWidget(HelpWidget* help)
{
    Help = help;
}

void startpage::goToHelp()
{    
        this->setEnabled(false);
        this->hide();
        Help->setEnabled(true);
        Help->show();
}

void startpage::openSettingsDialog()
{
    SettingsDialog settingsDialog(this);
    connect(&settingsDialog, &SettingsDialog::settingsChanged, this, &startpage::updateSettings);
    settingsDialog.exec();
}

void startpage::updateSettings(int volume, const QString& difficulty, int fps)
{
    musicVolume = volume;
    Difficulty = difficulty;
    fpsIndex = fps / 30;//����ˢ��֡��
}

void startpage::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // ��ʼ����
    QImage img(":/new/prefix1/Surface.png"); // ����ͼƬ��Դ
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // �������ڻ���ͼƬ
    mpainter_1->end(); // ��������
}

void startpage::initSettings()
{
    fpsIndex = 1;
    musicVolume = 50;
    Difficulty = "�е�";
    qInfo() << "init:" << fpsIndex;
}
