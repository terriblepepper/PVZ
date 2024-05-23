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
    this->initSettings();//初始化基本参数
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
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-options.png);" // 鼠标悬停样式 
                         "}");
    btn_help->setGeometry(728, 521, 59, 29);
    btn_help->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-help.png);" // 鼠标悬停样式 
                         "}");
    btn_exit->setGeometry(811, 510, 60, 30);
    btn_exit->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明        
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/menu-exit.png);" // 鼠标悬停样式 
                         "}");
    btn_adventure->setGeometry(450,60,340,120);
    btn_adventure->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明
                         "border-image:url(:/new/prefix1/mx1.png);" // 设置按钮样式，包括背景图片
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/mx.png);" // 鼠标悬停样式
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

     // 进入冒险
    connect(btn_adventure,&QPushButton::clicked,[this](){
        /*设置卡片冷却时间（在card.cpp设置会出现赋值失效）*/
        card::cool = { 227 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex };
        //loadingBGM->stop();
        game* ga=new game;
        this->setEnabled(false);
        this->close();
        ga->show();
    });
    //退出
    connect(btn_exit, &QPushButton::clicked, [this]() {
        QMessageBox exitBox;
        exitBox.setWindowTitle("退出");
        exitBox.setText("是否要退出游戏?");
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
    //帮助
    connect(btn_help, &QPushButton::clicked,this,&startpage::goToHelp);
    //设置
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
    fpsIndex = fps / 30;//设置刷新帧数
}

void startpage::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // 开始绘制
    QImage img(":/new/prefix1/Surface.png"); // 加载图片资源
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // 在主窗口绘制图片
    mpainter_1->end(); // 结束绘制
}

void startpage::initSettings()
{
    fpsIndex = 1;
    musicVolume = 50;
    Difficulty = "中等";
    qInfo() << "init:" << fpsIndex;
}
