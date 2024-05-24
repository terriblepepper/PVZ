#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <QPixmap>
#include "shop.h"
#include "map.h"
#include "shovel.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include "zombie.h"
#include "mower.h"
#include"gameIndex.h"
#include"gamingMenu.h"

class gamingMenuDialog;
class game : public QWidget
{
    Q_OBJECT
public:
    QTimer* mQTimer;
    QGraphicsView* view;
    QGraphicsScene* scene;
    explicit game(QWidget *parent = nullptr);
    ~game() override;
    void getGamingMenu(gamingMenuDialog* menuG);
    void game::checkGameState();//检测游戏状态
    void addZombie();//加入僵尸实现
    void bgmPlay();//bgm播放
    void goToGamingMenu();//打开游戏菜单
    gamingMenuDialog* gamingMenu;
    int level;//设置关卡
    QMediaPlayer* gamingBGM;
    QMediaPlaylist* gamingBGM_List;
    bool isInMenu = false;
};

#endif // GAME_H
