#include"gameSettings.h"
#include"gameIndex.h"
SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags & ~Qt::WindowCloseButtonHint);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setFixedSize(300, 300);
    // ������������
    volumeLabel = new QLabel("����:"+QString::number(musicVolume)+"%", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(musicVolume); // Ĭ��ֵ

    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeSlider);

    // �Ѷ�����
    QLabel* difficultyLabel = new QLabel("�Ѷ�", this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("��");
    difficultyComboBox->addItem("�е�");
    difficultyComboBox->addItem("����");
    difficultyComboBox->addItem("��̬");
    difficultyComboBox->setCurrentText(Difficulty);

    mainLayout->addWidget(difficultyLabel);
    mainLayout->addWidget(difficultyComboBox);

    // ֡������
    QLabel* fpsLabel = new QLabel("FPS", this);
    fpsComboBox = new QComboBox(this);
    fpsComboBox->addItem("30");
    fpsComboBox->addItem("60");
    fpsComboBox->addItem("90");
    fpsComboBox->addItem("120");
    fpsComboBox->setCurrentText(QString::number(fpsIndex * 30));

    mainLayout->addWidget(fpsLabel);
    mainLayout->addWidget(fpsComboBox);

    // ��ť����
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    applyButton = new QPushButton("Ӧ��", this);
    cancelButton = new QPushButton("ȡ��", this);
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // �����źźͲ�
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(volumeSlider, &QSlider::valueChanged, this, &SettingsDialog::updateVolumeLabel);
}

void SettingsDialog::applySettings()
{
    int volume = volumeSlider->value();
    QString difficulty = difficultyComboBox->currentText();
    int fps = fpsComboBox->currentText().toInt();

    emit settingsChanged(volume, difficulty, fps);
    accept();
}

void SettingsDialog::updateVolumeLabel()
{
    volumeLabel->setText("����:" + QString::number(volumeSlider->value()) + "%");
}
