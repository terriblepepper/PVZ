#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "gameIndex.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget* parent = nullptr);

signals:
    void settingsChanged(int volume, const QString& difficulty, int fps);

private slots:
    void applySettings();

private:
    QLabel* volumeLabel;
    QSlider* volumeSlider;
    QComboBox* difficultyComboBox;
    QComboBox* fpsComboBox;
    QPushButton* applyButton;
    QPushButton* cancelButton;
    void updateVolumeLabel();
};


