#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQueue>
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
#include <QKeyEvent>
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
class adventureGameMode : public QWidget {
    Q_OBJECT

public:
    explicit adventureGameMode(QWidget* parent = nullptr);
    ~adventureGameMode();
    void getGamingMenu(gamingMenuDialog* gM);
    HighPrecisionTimer* mQTimer;
    QGraphicsScene* scene;
    QMediaPlayer* gamingBGM = nullptr;
    QMediaPlaylist* gamingBGM_List =nullptr;
    static int level ;//关卡
    void startGame();
public slots:
    void checkGameState();
    void addZombie();
    void backFromSelect();
signals:
    void onBackClicked();
    void stopLoadingBGM();
    void resumeLoadingBGM();
    void gameFinish();
private:
    void setupUi();
    void initCardCool();
    void bgmPlay();
    void createMenuButton();
    void failScene();
    void winScene();
    void goToGamingMenu();
    void initIndex();
    bool loadLevelConfig(const QString& filePath, QQueue<QMap<QString, int>>& waves);
    QStackedWidget* Widget;
    QGraphicsView* view;
    gamingMenuDialog* gamingMenu;
    QPushButton* menuButton;
    QGraphicsProxyWidget* gamingWidgetsProxy;
    QPushButton* back = nullptr;
    CardSelectionDialog* adSelecting = nullptr;
    QPushButton* gameOverButton = nullptr;
    QPushButton* gameWinButton = nullptr;
    QMap<int, QPushButton*> btn_levelMap;
    int duration = 0;//每波完成后下一波间隔时间
    int time = 0;//定时器
    bool isRoundDone = true;
    QQueue<QMap<QString, int>> rounds;//记录每波僵尸的数量
};
