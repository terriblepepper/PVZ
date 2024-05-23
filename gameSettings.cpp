#include"gameSettings.h"
#include"gameIndex.h"
SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 音乐音量设置
    QLabel* volumeLabel = new QLabel("音量", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // 默认值

    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeSlider);

    // 难度设置
    QLabel* difficultyLabel = new QLabel("难度", this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("简单");
    difficultyComboBox->addItem("中等");
    difficultyComboBox->addItem("困难");
    difficultyComboBox->addItem("变态");

    mainLayout->addWidget(difficultyLabel);
    mainLayout->addWidget(difficultyComboBox);

    // 帧数设置
    QLabel* fpsLabel = new QLabel("FPS", this);
    fpsComboBox = new QComboBox(this);
    fpsComboBox->addItem("30");
    fpsComboBox->addItem("60");
    fpsComboBox->addItem("120");

    mainLayout->addWidget(fpsLabel);
    mainLayout->addWidget(fpsComboBox);

    // 按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    applyButton = new QPushButton("应用", this);
    cancelButton = new QPushButton("取消", this);
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // 连接信号和槽
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void SettingsDialog::applySettings()
{
    int volume = volumeSlider->value();
    QString difficulty = difficultyComboBox->currentText();
    int fps = fpsComboBox->currentText().toInt();

    emit settingsChanged(volume, difficulty, fps);
    accept();
}
