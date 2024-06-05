#include "gamingMenu.h"


gamingMenuDialog::gamingMenuDialog(QWidget* parent) : QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    this->setStyleSheet("font-size: 18px;font-family: MiSans");
    setWindowFlags(flags & ~Qt::WindowCloseButtonHint);
    // ������������
    volumeLabel = new QLabel("����:"+QString::number(musicVolume)+"%", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100); // ����������Χ��0��100
    volumeSlider->setValue(musicVolume);
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
    connect(volumeSlider, &QSlider::valueChanged, this, &gamingMenuDialog::onVolumeChanged);
    connect(restartButton, &QPushButton::clicked, this, &gamingMenuDialog::onRestartClicked);
    connect(mainMenuButton, &QPushButton::clicked, this, &gamingMenuDialog::onMainMenuClicked);
    connect(resumeButton, &QPushButton::clicked, this, &gamingMenuDialog::onResumeClicked);
    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(volumeLabel);
    layout->addWidget(volumeSlider);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);
    layout->addWidget(resumeButton);
    this->setFixedSize(300, 210);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setLayout(layout);
}


void gamingMenuDialog::getMainMenuPoints(startpage* menu)
{
    mainMenuPage = menu;
}

void gamingMenuDialog::getGameWindow(survivalGameMode* m1)
{
    survivalGaming = m1;
    currentGameMode = survivalGaming;
}

void gamingMenuDialog::getGameWindow(adventureGameMode* m2)
{
    adventureGaming = m2;
    currentGameMode = adventureGaming;
}

void gamingMenuDialog::getGameWindow(smallGameMode* m3)
{
    smallGaming = m3;
    currentGameMode =smallGaming;
}

void gamingMenuDialog::getCurrentGameMode(QWidget* current)
{
    currentGameMode = current;
}


void gamingMenuDialog::onVolumeChanged(int volume)
{
    // ���������仯
    musicVolume = volume;
    volumeLabel->setText("����:" + QString::number(musicVolume) + "%");

    if (currentGameMode == survivalGaming) {
        survivalGaming->gamingBGM->setVolume(musicVolume);
    }
    else if (currentGameMode == adventureGaming) {
        adventureGaming->gamingBGM->setVolume(musicVolume);
    }
    else if (currentGameMode == smallGaming)
    {
        smallGaming->gamingBGM->setVolume(musicVolume);
    }
}

void gamingMenuDialog::onRestartClicked()
{    
    if (currentGameMode == survivalGaming) {
        survivalGaming->close();
        survivalGaming->deleteLater();
        survivalGaming = new survivalGameMode;
        survivalGaming->getGamingMenu(this);
        currentGameMode = survivalGaming;
        emit restartGame(survivalGaming);
        survivalGaming->show();
    }
    else if (currentGameMode == adventureGaming) {
        adventureGaming->close();
        adventureGaming->deleteLater();
        adventureGaming = new adventureGameMode;
        adventureGaming->getGamingMenu(this);
        currentGameMode = adventureGaming;
        emit restartGame(adventureGaming);
        adventureGaming->show();
    }
    else if (currentGameMode == smallGaming)
    {
        smallGaming->close();
        smallGaming->deleteLater();
        smallGaming = new smallGameMode;
        smallGaming->getGamingMenu(this);
        currentGameMode = smallGaming;
        emit restartGame(smallGaming);
        smallGaming->show();
    }
    this->hide();
}

void gamingMenuDialog::onMainMenuClicked()
{
    emit gameToMainMenu();
}

void gamingMenuDialog::onResumeClicked()
{
    if (currentGameMode == survivalGaming) 
    {
        survivalGaming->gamingBGM->play();
        survivalGaming->mQTimer->resume();
    }
    else if (currentGameMode == adventureGaming) 
    {
        adventureGaming->gamingBGM->play();
        adventureGaming->mQTimer->resume();
    }
    else if (currentGameMode == smallGaming)
    {
        smallGaming->gamingBGM->play();
        smallGaming->mQTimer->resume();
    }
    this->hide(); // �رնԻ���
}
