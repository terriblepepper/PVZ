#pragma once
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include"game.h"
#include"gameIndex.h"
class gamingMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gamingMenuDialog(QWidget* parent = nullptr);

signals:
    void resumeGame();
    void restartGame();
    void gameToMainMenu();

private slots:
    void onVolumeChanged(int volume);
    void onRestartClicked();
    void onMainMenuClicked();
    void onResumeClicked();

private:
    QSlider* volumeSlider;
    QPushButton* restartButton;
    QPushButton* mainMenuButton;
    QPushButton* resumeButton;
};