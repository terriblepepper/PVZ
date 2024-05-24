#include "gamingMenu.h"

gamingMenuDialog::gamingMenuDialog(QWidget* parent) : QDialog(parent)
{
    // 创建音量滑块
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100); // 假设音量范围是0到100
    connect(volumeSlider, &QSlider::valueChanged, this, &gamingMenuDialog::onVolumeChanged);

    // 创建按钮
    restartButton = new QPushButton("重新开始", this);
    mainMenuButton = new QPushButton("主菜单", this);
    resumeButton = new QPushButton("返回游戏", this);

    QFont yaheiFont("Microsoft YaHei", 12);
    restartButton->setFont(yaheiFont);
    mainMenuButton->setFont(yaheiFont);
    resumeButton->setFont(yaheiFont);


    // 连接按钮信号
    connect(restartButton, &QPushButton::clicked, this, &gamingMenuDialog::onRestartClicked);
    connect(mainMenuButton, &QPushButton::clicked, this, &gamingMenuDialog::onMainMenuClicked);
    connect(resumeButton, &QPushButton::clicked, this, &gamingMenuDialog::onResumeClicked);

    // 设置布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(volumeSlider);
    layout->addWidget(restartButton);
    layout->addWidget(mainMenuButton);
    layout->addWidget(resumeButton);
    setLayout(layout);
}


void gamingMenuDialog::onVolumeChanged(int volume)
{
    // 处理音量变化
    // 这里可以调用游戏的音量控制函数
}

void gamingMenuDialog::onRestartClicked()
{
    // 发出重新开始游戏的信号
    emit restartGame();
}

void gamingMenuDialog::onMainMenuClicked()
{
    // 发出返回主菜单的信号
    emit gameToMainMenu();
}

void gamingMenuDialog::onResumeClicked()
{
    // 发出恢复游戏的信号
    emit resumeGame();
    close(); // 关闭对话框
}
