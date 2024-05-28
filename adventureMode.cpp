#include "adventureMode.h"

adventureGameMode::adventureGameMode(QWidget* parent) : QWidget(parent) {
    setupUi();
    setFixedSize(910, 610);
}

void adventureGameMode::goToGamingMenu()
{
    mQTimer->pause();
    gamingBGM->pause();
    gamingMenu->show();
}

void adventureGameMode::initIndex()
{
    duration = 30 * fpsIndex * 10;
    //加载关卡信息
    loadLevelConfig("./configs/levels/Level" + QString::number(level) + ".json", rounds);
}

bool adventureGameMode::loadLevelConfig(const QString& filePath, QQueue<QMap<QString, int>>& waves)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Couldn't open save file.";
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject json = loadDoc.object();
    for (const QString& key : json.keys())
    {
        QJsonArray waveArray = json[key].toArray();
        for (const QJsonValue& value : waveArray)
        {
            QJsonObject waveObject = value.toObject();
            QMap<QString, int> waveMap;
            for (auto it = waveObject.begin(); it != waveObject.end(); ++it)
            {
                waveMap.insert(it.key(), it.value().toInt());
            }
            waves.enqueue(waveMap);
        }
    }

    return true;
}

void adventureGameMode::setupUi() {
    card::cardSelectedMap.clear();//清空已选择卡片以防重复选择
     QVBoxLayout* mainLayout = new QVBoxLayout(this);
     back = new QPushButton("返回");
     back->setFixedSize(120, 40);
     back->move(790, back->y());
     back->setStyleSheet("QPushButton {"
         "border-image: url(:/new/prefix1/levelbutton.png) center no-repeat;" // 设置按钮样式，包括背景图片
         "font-size: 30px;" // 设置字体大小
         "font-weight: bold"
         "}"
         "QPushButton:hover {" // 鼠标悬停样式
         "color: green;" // 设置鼠标悬停时的字体颜色
         "border-image: url(:/new/prefix1/levelbutton1.png) center no-repeat;"
         "}");
     connect(this->back, &QPushButton::clicked, this, &adventureGameMode::onBackClicked);
     mainLayout->addWidget(back);

    // 创建堆栈式窗口
    Widget = new QStackedWidget(this);
    // 创建关卡选择页面
    QWidget* levelWidget = new QWidget();
    QVBoxLayout* levelLayout = new QVBoxLayout(levelWidget);
    QPixmap backgroundPixmap(":/new/prefix1/levelSelectBackground.jpg");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    levelWidget->setStyleSheet("background-image: url(:/new/prefix1/levelSelectBackground.jpg);");

    // 添加关卡选择按钮，这里假设有 20 个关卡
    for (int i = 1; i <= 20; ++i) {
        QPushButton* levelButton = new QPushButton(QString("关卡%1").arg(i));
        //设置button的工程名字
        levelButton->setObjectName(QString("level_%1").arg(i));
        levelButton->setFixedHeight(80);
        levelButton->setStyleSheet("QPushButton {"
            "border-image: url(:/new/prefix1/levelbutton.png) center no-repeat;" // 设置按钮样式，包括背景图片
            "font-size: 30px;" // 设置字体大小
            "font-weight: bold"
            "}"
            "QPushButton:hover {" // 鼠标悬停样式
            "color: green;" // 设置鼠标悬停时的字体颜色
            "border-image: url(:/new/prefix1/levelbutton1.png) center no-repeat;"
            "}");
        connect(levelButton, &QPushButton::clicked, [this, levelButton]() {
            emit stopLoadingBGM();
            adSelecting = new (CardSelectionDialog);
            adSelecting->setWindowFlags(adSelecting->windowFlags() | Qt::WindowStaysOnTopHint);
            adSelecting->isAdvMode = true;
            adSelecting->show();
            //接收恢复BGM信号
            connect(adSelecting, &CardSelectionDialog::resumeLevel_BGM, this, &adventureGameMode::backFromSelect);
            connect(adSelecting, &CardSelectionDialog::cardIsSelected, [this, levelButton]()  {
                QString temp = levelButton->objectName();
                level = temp.remove("level_").toInt();
                startGame();
                });
            });
        levelLayout->addWidget(levelButton);
        btn_levelMap.insert(i, levelButton);
    }

    QScrollArea* levelSelectArea = new QScrollArea();
    levelSelectArea->setWidgetResizable(true);
    levelSelectArea->setWidget(levelWidget);
    Widget->addWidget(levelSelectArea);
    // 创建游戏视图

    view = new QGraphicsView(this);
    view->setAlignment(Qt::AlignCenter);
    view->hide();  // 初始时隐藏视图

    mainLayout->addWidget(Widget);
    setLayout(mainLayout); // 设置布局到adventureGameMode窗口
}

void adventureGameMode::initCardCool()
{
    for (const auto& key : card::cardSelectedMap.keys()) {
        card::cardSelectedMap[key].cool = card::baseCardMap[key].cool * fpsIndex;
    }
}

void adventureGameMode::startGame() {
    //初始化参数
    initIndex();
    initCardCool();//设置卡片冷却时间

    //播放BGM
    bgmPlay();

    // 使用高精度定时器
    mQTimer = new HighPrecisionTimer(this);

    // 创建游戏场景并设置其分辨率
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600); // 控制img需要截取部分
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // 初始化其他组件
    shop* cardBar = new shop;
    cardBar->setPos(520, 45);
    scene->addItem(cardBar);

    shovel* sho = new shovel;
    sho->setPos(830, 40);
    scene->addItem(sho);

    Map* baseCardMap = new Map;
    baseCardMap->setPos(618, 326);
    scene->addItem(baseCardMap);

    // 设置视图属性并将场景添加到视图中
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //添加除草机
    for (int i = 0; i < 5; ++i) {
        Mower* mower = new Mower; 
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    const QList<QGraphicsItem*> items = scene->items();

    // 设置视图大小并显示
    view->resize(905, 605); // 确保视图大小与场景大小匹配
    view->move(0, 0); // 确保视图在窗口中的位置正确
    // 连接高精度定时器的timeout信号到场景的advance槽，实现场景中物体的动画效果
    connect(mQTimer, &HighPrecisionTimer::timeout, scene, &QGraphicsScene::advance);
    // 连接高精度定时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &adventureGameMode::addZombie);
    // 连接高精度定时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &adventureGameMode::checkGameState);
    mQTimer->start(33333 / fpsIndex); // 启动高精度定时器，以微秒为单位
    view->show();
    //添加菜单按钮
    createMenuButton();
    //连接到菜单按钮
    connect(menuButton, &QPushButton::clicked, this, &adventureGameMode::goToGamingMenu);
}

void adventureGameMode::checkGameState()
{
    //检查游戏是否结束，是否有僵尸到达屏幕最左边
    const QList<QGraphicsItem*> items = scene->items();
    int zombieCount = 0;
    qInfo() << "checkgamestate" << rounds.isEmpty() << items.isEmpty();
    if (!items.isEmpty())qInfo() << "survive:" << items.size();
    foreach(QGraphicsItem * item, items)
    {
        if (item->type() == zombie::Type)
        {
            if (item->x() < 150)
            {
                failScene();
            }
            zombieCount++;
        }
    }
    if (zombieCount <= 0 && rounds.isEmpty())
    {
        winScene();
    }
}

void adventureGameMode::addZombie()
{
    const QList<QGraphicsItem*> items = scene->items();
    int zombieCount = 0;
    for (QGraphicsItem* item : items)
    {
        if (item->type() == zombie::Type)
        {
            zombieCount++;
        }
    }
    //判断回合是否完成(僵尸没有并且不是第一回合和最后一回合)
    if (!isRoundDone && !rounds.isEmpty()&& zombieCount <=0 )
    {
        isRoundDone = true;
        time = 0;//重置计时器
    }
    //判断回合是否完成
    if (isRoundDone) 
    {
        ++time;
        if (time >= duration) //一波完成后，间隔duration的时间开始下一波
        {
            QMap<QString, int> round = rounds.dequeue();//获取队头地图元素，并将队头出队列
            for (auto& key : round.keys())
            {
                int num = round[key];//获取本轮键值僵尸的个数
                while (num)
                {
                    //放僵尸
                    int offsetX = qrand() % 80;
                    int randRoad = qrand() % 5;
                    zombie* zombie;
                    if (key == "basic")
                    {
                        zombie = new basiczombie;
                    }
                    else if (key == "cone")
                    {
                        zombie = new ConeZombie;
                    }
                    else if (key == "bucket")
                    {
                        zombie = new BucketZombie;
                    }
                    else if (key == "football")
                    {
                        zombie = new FootballZombie;
                    }
                    else if (key == "screen")
                    {
                        zombie = new ScreenZombie;
                    }
                    zombie->setPos(988 + offsetX, 120 + 95 * randRoad);
                    scene->addItem(zombie);
                    num--;
                }
                isRoundDone = false;
            }
        }
    }   
}

void adventureGameMode::backFromSelect()
{
    emit resumeLoadingBGM();
}

void adventureGameMode::bgmPlay()
{
    gamingBGM = new(QMediaPlayer);
    gamingBGM_List = new(QMediaPlaylist);
    // 添加MP3文件到播放列表
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/04Grasswalk.mp3"));
    // 设置播放模式为循环播放
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // 将播放列表设置给播放器
    gamingBGM->setPlaylist(gamingBGM_List);
    //设置音量
    gamingBGM->setVolume(musicVolume);
    // 开始播放音乐
    gamingBGM->play();

}

void adventureGameMode::createMenuButton()
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

void adventureGameMode::failScene()
{
    // 结束计时器停止游戏
    mQTimer->stop();

    // 添加游戏失败的结束图片
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
    connect(gameOverButton, &QPushButton::clicked, this, &adventureGameMode::gameFinish);
}

void adventureGameMode::winScene()
{
    // 结束计时器停止游戏
    mQTimer->stop();

    // 添加游戏胜利的结束图片
    scene->addPixmap(QPixmap(":/new/prefix1/gameWin.png"))->setPos(336, 92);
    gamingBGM->stop();
    gamingBGM->setMedia(QUrl::fromLocalFile("./sound/winmusic.mp3"));
    gamingBGM->play();
    scene->advance();

    // 创建一个透明的 QPushButton 覆盖整个窗口
    gameWinButton = new QPushButton();
    gameWinButton->setStyleSheet("background: transparent;");
    gameWinButton->setFlat(true);
    gameWinButton->setGeometry(0, 0, scene->width(), scene->height());

    // 将 QPushButton 添加到场景中
    gamingWidgetsProxy = scene->addWidget(gameWinButton);
    gamingWidgetsProxy->setPos(0, 0);
    connect(gameWinButton, &QPushButton::clicked, this, &adventureGameMode::gameFinish);
}

adventureGameMode::~adventureGameMode()
{
    if (gamingBGM) 
    {
        delete back;
        delete gamingBGM;
        delete gamingBGM_List;
        delete mQTimer;
        delete scene;
    }
    delete view;
}

void adventureGameMode::getGamingMenu(gamingMenuDialog* gM) {
    gamingMenu = gM;
}
