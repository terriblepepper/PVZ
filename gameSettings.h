//utf8
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
    void settingsChanged(int volumeBGM,int volumeItem, const QString& difficulty, int fps);

private slots:
    void applySettings();

private:
    QLabel* volumeLabel;
    QSlider* volumeSlider;
    QLabel* itemVolumeLabel;
    QSlider* itemVolumeSlider;
    QComboBox* difficultyComboBox;
    QComboBox* fpsComboBox;
    QPushButton* applyButton;
    QPushButton* cancelButton;
    void updateVolumeLabel();
};


