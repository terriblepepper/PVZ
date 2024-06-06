#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#pragma once
#include<qdebug.h>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <QPixmap>
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
#include"apolozombie.h"
#include"cleopatrazombie.h"
#include"pharaohzombie.h"
#include"pyramidzombie.h"
#include "zombie.h"
#include "mower.h"
#include"gameIndex.h"
#include"gamingMenu.h"
#include "highprecesionQtimer.h" // �����߾��ȶ�ʱ����ͷ�ļ�.

class gamingMenuDialog;
class survivalGameMode : public QWidget {
    Q_OBJECT
public:
    explicit survivalGameMode(QWidget* parent = nullptr);
    ~survivalGameMode() override;
    void getGamingMenu(gamingMenuDialog* menuG);
    void checkGameState();
    void addZombie();
    void goToGamingMenu();
    gamingMenuDialog* gamingMenu;
    QMediaPlayer* gamingBGM;
    QMediaPlaylist* gamingBGM_List;
    TimerThread* mQTimer; // ʹ�ø߾��ȶ�ʱ��
    QGraphicsView* view;
    QGraphicsScene* scene;
public slots:
    void handleVolumeChange();
    void initTimer();
signals:
    void gameOver();
private:
    void bgmPlay();
    void initIndex();
    void createMenuButton();
    QPushButton* gameOverButton;
    QPushButton* menuButton;
    QGraphicsProxyWidget* gamingWidgetsProxy;
    int low;
    int high;
    int maxtime;//��ʼ������ʬ���ʱ��
    int time;
    int counter;
};

// SURVIVALGAMEMODE_H


