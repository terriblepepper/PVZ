#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include"startpage.h"
#include"survivalMode.h"
#include"adventureMode.h"
#include"smallgameMode.h"
#include"gameIndex.h"
#include"card.h"
#include"gameIndex.h"


class startpage;
class survivalGameMode;
class adventureGameMode;
class smallGameMode;
class gamingMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gamingMenuDialog(QWidget* parent = nullptr);
    void getMainMenuPoints(startpage* menu);
    void getGameWindow(survivalGameMode* m1);
    void getGameWindow(adventureGameMode* m2);
    void getGameWindow(smallGameMode* m3);
    void getCurrentGameMode(QWidget* current);
    startpage* mainMenuPage;
    QWidget* currentGameMode = nullptr; // 保存当前游戏模式的指针
    survivalGameMode* survivalGaming;
    adventureGameMode* adventureGaming;
    smallGameMode* smallGaming;
signals:
    void restartGame(survivalGameMode* t1);
    void restartGame(adventureGameMode* t2);
    void restartGame(smallGameMode* t3);
    void gameToMainMenu();
    void changeVolume();//告诉主菜单更新音量
private slots:
    void onVolumeChanged(int volume);
    void onRestartClicked();
    void onMainMenuClicked();
    void onResumeClicked();

private:
    QLabel* volumeLabel;
    QSlider* volumeSlider;
    QPushButton* restartButton;
    QPushButton* mainMenuButton;
    QPushButton* resumeButton;
};