#include"gameSettings.h"
#include"gameIndex.h"
SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags & ~Qt::WindowCloseButtonHint);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setFixedSize(300, 400);
    // 音乐音量设置
    volumeLabel = new QLabel("音乐:"+QString::number(musicVolume)+"%", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(musicVolume); // 默认值
    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeSlider);
    //游戏音效设置
    itemVolumeLabel = new QLabel("音效:" + QString::number(itemVolume) + "%", this);
    itemVolumeSlider = new QSlider(Qt::Horizontal, this);
    itemVolumeSlider->setRange(0, 100);
    itemVolumeSlider->setValue(itemVolume); // 默认值
    mainLayout->addWidget(itemVolumeLabel);
    mainLayout->addWidget(itemVolumeSlider);
    // 难度设置
    QLabel* difficultyLabel = new QLabel("难度", this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("简单");
    difficultyComboBox->addItem("中等");
    difficultyComboBox->addItem("困难");
    difficultyComboBox->addItem("变态");
    difficultyComboBox->setCurrentText(Difficulty);

    mainLayout->addWidget(difficultyLabel);
    mainLayout->addWidget(difficultyComboBox);

    // 帧数设置
    QLabel* fpsLabel = new QLabel("FPS", this);
    fpsComboBox = new QComboBox(this);
    fpsComboBox->addItem("30");
    fpsComboBox->addItem("60");
    fpsComboBox->addItem("90");
    fpsComboBox->addItem("120");
    fpsComboBox->setCurrentText(QString::number(fpsIndex * 30));

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
    connect(volumeSlider, &QSlider::valueChanged, this, &SettingsDialog::updateVolumeLabel);
    connect(itemVolumeSlider, &QSlider::valueChanged, this, &SettingsDialog::updateVolumeLabel);
}

void SettingsDialog::applySettings()
{
    int volume = volumeSlider->value();
    int volume2 = itemVolumeSlider->value();
    QString difficulty = difficultyComboBox->currentText();
    int fps = fpsComboBox->currentText().toInt();

    emit settingsChanged(volume,volume2, difficulty, fps);
    accept();
}

void SettingsDialog::updateVolumeLabel()
{
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if(senderSlider == volumeSlider)
        volumeLabel->setText("音量:" + QString::number(volumeSlider->value()) + "%");
    else
        itemVolumeLabel->setText("音效:" + QString::number(itemVolumeSlider->value()) + "%");
}
