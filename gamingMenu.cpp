#include "gamingMenu.h"
#include"game.h"
#include"gameIndex.h"
#include"startpage.h"
#include"card.h"
#include"startpage.h"

gamingMenuDialog::gamingMenuDialog(QWidget* parent) : QDialog(parent)
{
    setFixedSize(300, 400);
    // ������������
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100); // ����������Χ��0��100
    connect(volumeSlider, &QSlider::valueChanged, this, &gamingMenuDialog::onVolumeChanged);

    // ������ť
    restartButton = new QPushButton("���¿�ʼ", this);
    mainMenuButton = new QPushButton("���˵�", this);
    resumeButton = new QPushButton("������Ϸ", this);

    QFont yaheiFont("Microsoft YaHei", 12);
    restartButton->setFont(yaheiFont);
    mainMenuButton->setFont(yaheiFont);
    resumeButton->setFont(yaheiFont);


    // ���Ӱ�ť�ź�
    connect(restartButton, &QPushButton::clicked, this, &gamingMenuDialog::onRestartClicked);
    connect(mainMenuButton, &QPushButton::clicked, this, &gamingMenuDialog::onMainMenuClicked);
    connect(resumeButton, &QPushButton::clicked, this, &gamingMenuDialog::onResumeClicked);
    connect(this, &QDialog::rejected, this, &gamingMenuDialog::onResumeClicked);
    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(volumeSlider);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);
    layout->addWidget(resumeButton);
    setLayout(layout);
}


void gamingMenuDialog::getMainMenuPoints(startpage* menu)
{
    mainMenuPage = menu;
}

void gamingMenuDialog::getGameWindow(game* game)
{
    gaming = game;
}

void gamingMenuDialog::onVolumeChanged(int volume)
{
    // ���������仯
    // ������Ե�����Ϸ���������ƺ���
}

void gamingMenuDialog::onRestartClicked()
{
    // �������¿�ʼ��Ϸ���ź�
    //emit restartGame();
    gaming->deleteLater();
    card::cool = { 227 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex };
    gaming = new (game);
    gaming->show();
    close();
}

void gamingMenuDialog::onMainMenuClicked()
{
    this->close();
    gaming->deleteLater();
    this->deleteLater();
    mainMenuPage->show();
}

void gamingMenuDialog::onResumeClicked()
{
    // �����ָ���Ϸ���ź�
    //emit resumeGame();
    gaming->gamingBGM->play();
    gaming->mQTimer->start(33/fpsIndex);
    close(); // �رնԻ���
}
