#include<qdebug.h>
#include "game.h"

game::game(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(910, 610);  
    mQTimer=new QTimer(this);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(150,0,900,600);//控制img需要截取部分
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //视图显示的坐标，注意所有的坐标都是基于未被裁剪图片的坐标
    //(290,120,10,10);(1,1)坐标(中心坐标)
    //245,175->330,270->>>>格子85 95
    shop *cardBar = new shop;
    cardBar->setPos(520, 45);
    scene->addItem(cardBar);
    shovel *sho = new shovel;
    sho->setPos(830, 40);
    scene->addItem(sho);
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);
    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;//放置推土机
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    //bgm播放
    bgmPlay();
    // 创建视图对象并设置属性
    view = new QGraphicsView(scene, this);
    view->resize(905, 605);//设置绘制窗口大小
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //创建按钮等控件渲染
    QPushButton*menuButton = new QPushButton;// 创建菜单按钮
    menuButton->setFixedSize(136, 36); // 设置按钮大小

    // 设置按钮的样式表，包括普通状态和悬停状态下的背景图片
    menuButton->setStyleSheet("QPushButton {"
        "    border-image: url(:/new/prefix1/gamingMenu.png);"
        "}"
        "QPushButton:hover {"
        "    border-image: url(:/new/prefix1/gamingMenu1.png);"
        "}");

    // 将菜单按钮嵌入到 QGraphicsProxyWidget
    QGraphicsProxyWidget* gamingWidgetsProxy = scene->addWidget(menuButton);
    gamingWidgetsProxy->setPos(894, 0); // 设置按钮在场景中的位置

    // 将菜单按钮添加到场景
    scene->addItem(gamingWidgetsProxy);
    //连接菜单按钮
    connect(menuButton, &QPushButton::clicked, this, &game::goToGamingMenu);
    // 连接计时器的timeout信号到场景的advance槽，实现场景中物体的动画效果
    connect(mQTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    // 连接计时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &QTimer::timeout, this, &game::addZombie);
    // 连接计时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &QTimer::timeout, this, &game::checkGameState);
    mQTimer->start(33 / fpsIndex); // 启动计时器，(33 / fpsIndex)每毫秒触发一次timeout信号，驱动游戏动画效果
    //qInfo() << "qTimer:" << mQTimer->interval();
    view->show(); // 显示视图
}
game::~game()
{
    delete gamingBGM;
    delete gamingBGM_List;
    delete mQTimer;
    delete view;
    delete scene;
}

void game::getGamingMenu(gamingMenuDialog* menuG)
{
    gamingMenu = menuG;
}

void game::addZombie()
{
   
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / (33 / fpsIndex);//初始最大出僵尸间隔时间
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        low++;
        if (low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }//随着游戏时间增加提高僵尸出现频率
        counter = 0;
        time = qrand() % (2 * maxtime / 3) + maxtime / 3;
        int type = qrand() % 100;
        int i = qrand() % 5;
        zombie* zombie;
        if (type < 40)
            zombie = new basiczombie;
        else if (type < 70)
            zombie = new ConeZombie;
        else if (type < 80)
            zombie = new BucketZombie;
        else if (type < 90)
            zombie = new ScreenZombie;
        else if(mQTimer)
            zombie = new FootballZombie;
        zombie->setPos(1028, 120 + 95 * i);
        scene->addItem(zombie);
    }

}

void game::bgmPlay()
{
    
    gamingBGM = new(QMediaPlayer);
    gamingBGM_List = new(QMediaPlaylist);
    // 添加多个MP3文件到播放列表
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/20. Grasswalk IN-GAME.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/13. Graze the Roof.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/06. Moongrains.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/09. Watery Graves (fast).mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/12. Cerebrawl.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/11. Rigor Mormist.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/05. Loonboon.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/14. Brainiac Maniac.mp3"));
    // 设置播放模式为循环播放
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // 将播放列表设置给播放器
    gamingBGM->setPlaylist(gamingBGM_List);
    
    // 设置随机种子
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    // 随机选取一个音乐进行播放
    int index = qrand() % gamingBGM_List->mediaCount(); // 随机生成音乐索引
    qDebug() << "Initial song index:" << index;
    gamingBGM_List->setCurrentIndex(index); // 设置当前播放音乐
    
    // 开始播放音乐
    gamingBGM->play();
    
}

void game::goToGamingMenu()
{
    //gamingMenuDialog* gamingMenu = new(gamingMenuDialog);
    mQTimer->stop();
    gamingBGM->pause();
    gamingMenu->show();
}

void game::checkGameState()
{
    //检查游戏是否结束，是否有僵尸到达屏幕最左边
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
    {
        if (item->type() == zombie::Type && item->x() < 150)
        {
            //如果有僵尸到达屏幕最左边，游戏结束
            scene->addPixmap(QPixmap(":/new/prefix1/ZombiesWon.png"))->setPos(336, 92);
            scene->advance();
            mQTimer->stop(); //结束计时器停止游戏
            return;
        }
    }
}