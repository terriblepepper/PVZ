#include"gameSettings.h"
#include"gameIndex.h"
SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // ������������
    QLabel* volumeLabel = new QLabel("����", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // Ĭ��ֵ

    mainLayout->addWidget(volumeLabel);
    mainLayout->addWidget(volumeSlider);

    // �Ѷ�����
    QLabel* difficultyLabel = new QLabel("�Ѷ�", this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("��");
    difficultyComboBox->addItem("�е�");
    difficultyComboBox->addItem("����");
    difficultyComboBox->addItem("��̬");

    mainLayout->addWidget(difficultyLabel);
    mainLayout->addWidget(difficultyComboBox);

    // ֡������
    QLabel* fpsLabel = new QLabel("FPS", this);
    fpsComboBox = new QComboBox(this);
    fpsComboBox->addItem("30");
    fpsComboBox->addItem("60");
    fpsComboBox->addItem("120");

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
}

void SettingsDialog::applySettings()
{
    int volume = volumeSlider->value();
    QString difficulty = difficultyComboBox->currentText();
    int fps = fpsComboBox->currentText().toInt();

    emit settingsChanged(volume, difficulty, fps);
    accept();
}
