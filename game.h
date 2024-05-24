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
class game : public QWidget
{
    Q_OBJECT
public:
    QTimer* mQTimer;
    QGraphicsView* view;
    QGraphicsScene* scene;
    explicit game(QWidget *parent = nullptr);
    ~game() override;
    void game::checkGameState();//检测游戏状态
    void addZombie();//加入僵尸实现
    void bgmPlay();
    
    int level;//设置关卡
signals:

private:
    QMediaPlayer* gamingBGM;
    QMediaPlaylist* gamingBGM_List;
};

#endif // GAME_H
