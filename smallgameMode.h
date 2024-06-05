//utf8
#pragma once
#include<QFile>
#include <QMap>
#include <QWidget>
#include <QGraphicsView>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include "shop.h"
#include "map.h"
#include "shovel.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include"gargantuarzombie.h"
#include"flagzombie.h"
#include"smallzombie.h"
#include"yetizombie.h"
#include"icetrackerzombie.h"
#include"apolozombie.h"
#include"cleopatrazombie.h"
#include"pharaohzombie.h"
#include"pyramidzombie.h"
#include "zombie.h"
#include "mower.h"
#include"gameIndex.h"
#include"gamingMenu.h"
#include"highprecesionQtimer.h"
#include"CardSelectionDialog.h"

class card;
class gamingMenuDialog;
class HighPrecisionTimer;
class CardSelectionDialog;
class zombie;
class smallGameMode : public QWidget {
    Q_OBJECT

public:
    explicit smallGameMode(QWidget* parent = nullptr);
    ~smallGameMode();
    void getGamingMenu(gamingMenuDialog* gM);
    TimerThread* mQTimer;
    QGraphicsScene* scene;
    QMediaPlayer* gamingBGM = nullptr;
    QMediaPlaylist* gamingBGM_List = nullptr;
    static int level;//关卡
    void startGame();
public slots:
    void checkGameState();
    void addZombie();
signals:
    void onBackClicked();
    void stopLoadingBGM();
    void resumeLoadingBGM();
    void gameFinish();
private:
    void setupUi();
    void initIndex();
    void loadCards(const QString& filename);
    void bgmPlay();
    void createMenuButton();
    void failScene();
    void winScene();
    void goToGamingMenu();
    QStackedWidget* Widget;
    QGraphicsView* view;
    gamingMenuDialog* gamingMenu;
    QPushButton* menuButton;
    QGraphicsProxyWidget* gamingWidgetsProxy;
    QPushButton* back = nullptr;
    QPushButton* gameOverButton = nullptr;
    QPushButton* gameWinButton = nullptr;
    QMap<int, QPushButton*> btn_levelMap;
    int low;
    int high;
    int maxtime;//初始最大出僵尸间隔时间
    int time;
    int counter;
    int timeCounter = 0;//记录游戏时长
};
