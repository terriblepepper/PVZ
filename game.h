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
    void game::checkGameState();//�����Ϸ״̬
    void addZombie();//���뽩ʬʵ��
    void bgmPlay();//bgm����
    void goToGamingMenu();//����Ϸ�˵�
    gamingMenuDialog* gamingMenu;
    int level;//���ùؿ�
    QMediaPlayer* gamingBGM;
    QMediaPlaylist* gamingBGM_List;
    bool isInMenu = false;
};

#endif // GAME_H
