#include "survivalMode.h"

survivalGameMode::survivalGameMode(QWidget* parent)
    : QWidget{ parent }, mQTimer(new HighPrecisionTimer(this)), view(nullptr), scene(nullptr), gamingMenu(nullptr),
gamingBGM(nullptr), gamingBGM_List(nullptr) 
{   
    initIndex();
    /* 创建窗口 */
    this->setFixedSize(910, 610);

    // 使用高精度定时器
    mQTimer = new HighPrecisionTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600); // 控制img需要截取部分
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // 初始化其他组件（保持不变）
    shop* cardBar = new shop;
    cardBar->setPos(520, 45);
    scene->addItem(cardBar);
    shovel* sho = new shovel;
    sho->setPos(830, 40);
    scene->addItem(sho);
    Map* baseCardMap = new Map;
    baseCardMap->setPos(618, 326);
    scene->addItem(baseCardMap);
    for (int i = 0; i < 5; ++i) {
        Mower* mower = new Mower; // 放置推土机
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    // bgm播放
    bgmPlay();
    // 创建视图对象并设置属性
    view = new QGraphicsView(scene, this);
    view->resize(905, 605); // 设置绘制窗口大小
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    // 创建按钮等控件渲染
    createMenuButton();
    // 连接菜单按钮
    connect(menuButton, &QPushButton::clicked, this, &survivalGameMode::goToGamingMenu);
    // 连接高精度定时器的timeout信号到场景的advance槽，实现场景中物体的动画效果
    connect(mQTimer, &HighPrecisionTimer::timeout, scene, &QGraphicsScene::advance);
    // 连接高精度定时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &survivalGameMode::addZombie);
    // 连接高精度定时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &survivalGameMode::checkGameState);
    mQTimer->start(33333 / fpsIndex); // 启动高精度定时器，以微秒为单位
    qInfo() << "High precision timer started with interval:" << 33333 / fpsIndex << " microseconds";
    view->show(); // 显示视图
}

survivalGameMode::~survivalGameMode() {
    delete gamingBGM;
    delete gamingBGM_List;
    delete mQTimer;
    delete view;
    delete scene;
}


void survivalGameMode::getGamingMenu(gamingMenuDialog* menuG)
{
    gamingMenu = menuG;
}

void survivalGameMode::addZombie()
{
    //qInfo() << "low:" << low;
    if (++counter >= time)
    {
        low++;
        if (low > high)
        {
            maxtime /= 1.3;
            high *= 2.2;
        }//随着游戏时间增加提高僵尸出现频率
        counter = 0;
        time = qrand() % (2 * maxtime / 3) + maxtime / 3;
        int type = qrand() % 105;
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
        else if (type < 100)
            zombie = new FootballZombie;
        else if (type < 105)
            zombie = new gargantuarzombie;
        zombie->setPos(1028, 120 + 95 * i);
        scene->addItem(zombie);
    }

}

void survivalGameMode::bgmPlay()
{

    gamingBGM = new(QMediaPlayer);
    gamingBGM_List = new(QMediaPlaylist);
    // 添加多个MP3文件到播放列表
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/04Grasswalk.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/05LoonBoon.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/06Moongrains.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/09WaterGraves.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/11RigorMormist.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/12cerebrawl.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/14BrainiacManiac.mp3"));
    // 设置播放模式为循环播放
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // 将播放列表设置给播放器
    gamingBGM->setPlaylist(gamingBGM_List);

    // 设置随机种子
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    // 随机选取一个音乐进行播放
    int index = qrand() % gamingBGM_List->mediaCount(); // 随机生成音乐索引
    gamingBGM_List->setCurrentIndex(index); // 设置当前播放音乐
    gamingBGM->setVolume(musicVolume);
    // 开始播放音乐
    gamingBGM->play();

}

void survivalGameMode::goToGamingMenu()
{
    mQTimer->pause();
    gamingBGM->pause();
    gamingMenu->show();
}

void survivalGameMode::handleVolumeChange()
{
    gamingBGM->setVolume(musicVolume);
}

void survivalGameMode::initIndex()
{
    low = 4 * fpsIndex;
    high = 9 * fpsIndex;
    maxtime = 20 * fpsIndex * 1000000 / 33333;//初始最大出僵尸间隔时间
    time = maxtime / 2;
    counter = 0;
}

void survivalGameMode::createMenuButton()
{
    menuButton = new QPushButton; // 创建菜单按钮
    menuButton->setFixedSize(136, 36); // 设置按钮大小

    // 设置按钮的样式表，包括普通状态和悬停状态下的背景图片
    menuButton->setStyleSheet("QPushButton {"
        "    border-image: url(:/new/prefix1/gamingMenu.png);"
        "}"
        "QPushButton:hover {"
        "    border-image: url(:/new/prefix1/gamingMenu1.png);"
        "}");

    // 将菜单按钮嵌入到 QGraphicsProxyWidget
    gamingWidgetsProxy = scene->addWidget(menuButton);
    gamingWidgetsProxy->setPos(894, 0); // 设置按钮在场景中的位置
    // 将菜单按钮添加到场景
    scene->addItem(gamingWidgetsProxy);
}

void survivalGameMode::checkGameState()
{
    //检查游戏是否结束，是否有僵尸到达屏幕最左边
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
    {
        if (item->type() == zombie::Type && item->x() < 150)
        {
            // 结束计时器停止游戏
            mQTimer->stop();

            // 添加游戏结束图片
            scene->addPixmap(QPixmap(":/new/prefix1/ZombiesWon.png"))->setPos(336, 92);
            gamingBGM->stop();
            gamingBGM->setMedia(QUrl::fromLocalFile("./sound/losemusic.mp3"));
            gamingBGM->play();
            scene->advance();
            // 创建一个透明的 QPushButton 覆盖整个窗口
            gameOverButton = new QPushButton();
            gameOverButton->setStyleSheet("background: transparent;");
            gameOverButton->setFlat(true);
            gameOverButton->setGeometry(0, 0, scene->width(), scene->height());

            // 将 QPushButton 添加到场景中
            gamingWidgetsProxy = scene->addWidget(gameOverButton);
            gamingWidgetsProxy->setPos(0, 0);
            connect(gameOverButton, &QPushButton::clicked,this,&survivalGameMode::gameOver );

        }
    }
}