#include "gamingMenu.h"

gamingMenuDialog::gamingMenuDialog(QWidget* parent) : QDialog(parent)
{
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

    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(volumeSlider);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);
    layout->addWidget(resumeButton);
    setLayout(layout);
}


void gamingMenuDialog::onVolumeChanged(int volume)
{
    // ���������仯
    // ������Ե�����Ϸ���������ƺ���
}

void gamingMenuDialog::onRestartClicked()
{
    // �������¿�ʼ��Ϸ���ź�
    emit restartGame();
}

void gamingMenuDialog::onMainMenuClicked()
{
    // �����������˵����ź�
    emit gameToMainMenu();
}

void gamingMenuDialog::onResumeClicked()
{
    // �����ָ���Ϸ���ź�
    emit resumeGame();
    close(); // �رնԻ���
}
