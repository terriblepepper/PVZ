#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include"startpage.h"
#include"game.h"
#include"gameIndex.h"
#include"startpage.h"
#include"card.h"

class startpage;
class game;
class gamingMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gamingMenuDialog(QWidget* parent = nullptr);
    void getMainMenuPoints(startpage* menu);
    void getGameWindow(game* game);
    startpage* mainMenuPage;
    game* gaming;
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