#include"gargantuarzombie.h"
#include"gameIndex.h"
#include<QDebug>
#include"adventureMode.h"
gargantuarzombie::gargantuarzombie()
{
    hp = 3000.0; 
    atk = 1500.0 / (30 * (double)fpsIndex);
    speed = 4.2 * (33333.0 / (double)fpsIndex) / 1000000.0;
    zmSound = new QMediaPlayer;
    zmSoundList = new QMediaPlaylist;
    zmSoundList->addMedia(QUrl::fromLocalFile("./sound/gargantuar_thump.mp3"));
    zmSoundList->setPlaybackMode(QMediaPlaylist::Loop);
    zmSound->setMedia(zmSoundList);
    if (adventureGameMode::level < 16 && adventureGameMode::level>10)
    {
        setMovie("./images/newZombies/gargantuar2/walk.gif");

    }
    else
    {
        setMovie(":/new/prefix1/newZombies/gargantuar/walk_noimp.gif");
    } 
}

void gargantuarzombie::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新基础僵尸的绘制
    if (hp <= 0) // 如果基础僵尸的生命值小于等于0，表示已经被击败
    {
        if (state < 2) // 如果基础僵尸的状态小于2，表示处于死亡状态
        {
            state = 2; // 将状态设置为2（死亡）
            zmSound->stop();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie("./images/newZombies/gargantuar2/death.gif");

            }
            else
            {
                setMovie(":/new/prefix1/newZombies/gargantuar/death_noimp.gif");
            }
            
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; 
        return;
    }
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty()) // 如果基础僵尸与其他图形项发生碰撞
    {
        plant* pl = qgraphicsitem_cast<plant*>(items[0]);
        pl->hp -= atk; // 减少植物的生命值，受到基础僵尸的攻击
        if (state != 1) // 如果基础僵尸的状态不为1（攻击状态）
        {
            state = 1; // 将状态设置为1（攻击）
            zmSound->play();
            if (adventureGameMode::level < 16 && adventureGameMode::level>10)
            {
                setMovie("./images/newZombies/gargantuar2/eat.gif");

            }
            else
            {
                setMovie(":/new/prefix1/newZombies/gargantuar/smash_noimp.gif");
            }
        }
        return;
    }
    if (state) // 如果基础僵尸的状态不为0（行走状态）
    {
        state = 0; // 将状态设置为0（行走）
        zmSound->stop();
        if (adventureGameMode::level < 16 && adventureGameMode::level>10)
        {
            setMovie("./images/newZombies/gargantuar2/walk.gif");

        }
        else
        {
            setMovie(":/new/prefix1/newZombies/gargantuar/walk_noimp.gif");
        }
    }
    setX(x() - speed); // 更新基础僵尸的位置，让其向左移动
}

void gargantuarzombie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QImage image = mQMovie->currentImage(); // 获取当前帧的图片

    if (isSnow && state != 3)
    {
        // 设置帧图片的部分像素的颜色为灰色，用于表示僵尸被减速状态
        if (state != 2) // 如果状态不为2（僵尸普通状态），设置帧播放速度为50
            mQMovie->setSpeed(50);
        int w = image.width();
        int h = image.height();
        for (int i = 0; i < h; ++i)
        {
            uchar* line = image.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 200; // 将帧图片的像素的红色通道设置为200，即变为灰色
        }
    }

    // 在画布上绘制僵尸的帧图片
    painter->drawImage(QRectF(-140, -200, 280, 280), image); 
}

QRectF gargantuarzombie::boundingRect() const
{
    // 设置僵尸的边界矩形
    return QRectF(-160, -200, 400, 280);
}

