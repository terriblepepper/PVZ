#include "adventureMode.h"

int adventureGameMode::level = 0;
adventureGameMode::adventureGameMode(QWidget* parent) : QWidget(parent) {
    setupUi();
}

void adventureGameMode::goToGamingMenu()
{
    QMediaPlayer* sound = new QMediaPlayer(this);
    sound->setMedia(QUrl::fromLocalFile("./sound/pause.mp3"));
    sound->setVolume(itemVolume);
    sound->play();
    QGraphicsScene* catchScene = scene;
    mapScenes[catchScene].count++;
    QTimer::singleShot(250, [sound, catchScene]()
        {
            if (mapScenes[catchScene].isValid != false)
            {
                delete sound;
                mapScenes[catchScene].count--;
            }
            else
            {
                if (mapScenes[catchScene].count)
                {
                    mapScenes[catchScene].count--;
                }
                if (mapScenes[catchScene].count == 0)
                {
                    mapScenes.erase(catchScene);
                }
            }
        });
    mQTimer->pause();
    gamingBGM->pause();
    this->setEnabled(false);
    gamingMenu->show();
}

void adventureGameMode::initIndex()
{
    duration = 30 * fpsIndex * 10;
    //加载关卡信息
    loadLevelConfig("./configs/levels/Level" + QString::number(adventureGameMode::level) + ".json", rounds);
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
    setFixedSize(910, 610);
    setWindowTitle("PlantsVsZombies");
    setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // 设置窗口图标
    adventureGameMode::level = 0;//重置关卡
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

    // 添加关卡选择按钮，这里有20个关卡
    for (int i = 1; i <= 20; ++i) {
        QPushButton* levelButton = new QPushButton;
        if (i > 0 && i < 6)
            levelButton->setText("白天：" + QString("关卡%1").arg(i));
        else if (i > 5 && i < 11)
            levelButton->setText("黑夜：" + QString("关卡%1").arg(i));
        else if (i > 10 && i < 16)
            levelButton->setText("玛雅：" + QString("关卡%1").arg(i));
        else if (i > 15 && i < 21)
            levelButton->setText("屋顶：" + QString("关卡%1").arg(i));
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
            this->hide();
            QString temp = levelButton->objectName();
            adventureGameMode::level = temp.remove("level_").toInt();//按下关卡按钮就立马设置关卡
            emit stopLoadingBGM();
            adSelecting = new (CardSelectionDialog);
            adSelecting->setWindowFlags(adSelecting->windowFlags() | Qt::WindowStaysOnTopHint);
            adSelecting->isAdvMode = true;
            adSelecting->show();
            //接收恢复BGM信号
            connect(adSelecting, &CardSelectionDialog::resumeLevel_BGM, this, &adventureGameMode::backFromSelect);
            connect(adSelecting, &CardSelectionDialog::cardIsSelected, [this, levelButton]() {
                this->show();
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
    setWindowTitle("PlantsVsZombies | Level" + QString::number(adventureGameMode::level));
    //初始化参数
    initIndex();
    initCardCool();//设置卡片冷却时间

    // 使用高精度定时器
    mQTimer = new TimerThread(this);

    // 创建游戏场景并设置其分辨率
    scene = new QGraphicsScene(view);
    scene->setSceneRect(150, 0, 900, 600); // 控制img需要截取部分
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneCast Cast;
    Cast.isValid = true;
    Cast.count = 0;
    Cast.soundsCount = 0;
    mapScenes.emplace(scene,Cast);
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
    if (adventureGameMode::level < 6)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    else if (adventureGameMode::level > 5 && adventureGameMode::level < 11)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background2.jpg")); // 设置背景图片
    else if (adventureGameMode::level > 10 && adventureGameMode::level < 16)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background3.jpg")); // 设置背景图片
    else if (adventureGameMode::level > 15 && adventureGameMode::level <= 20)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background4.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);

    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //添加除草机
    for (int i = 0; i < 5; ++i) {
        Mower* mower = new Mower;
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    // 设置视图大小并显示
    view->resize(905, 605); // 确保视图大小与场景大小匹配
    view->move(0, 0); // 确保视图在窗口中的位置正确
    // 连接高精度定时器的timeout信号到场景的advance槽，实现场景中物体的动画效果
    connect(mQTimer, &TimerThread::timeout, scene, &QGraphicsScene::advance);
    // 连接高精度定时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &TimerThread::timeout, this, &adventureGameMode::addZombie);
    // 连接高精度定时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &TimerThread::timeout, this, &adventureGameMode::checkGameState);
    //添加菜单按钮
    createMenuButton();
    //连接到菜单按钮
    connect(menuButton, &QPushButton::clicked, this, &adventureGameMode::goToGamingMenu);
    view->show();
    //播放BGM
    bgmPlay();
    
}

void adventureGameMode::checkGameState()
{
    //检查游戏是否结束，是否有僵尸到达屏幕最左边
    const QList<QGraphicsItem*> items = scene->items();
    int zombieCount = 0;
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
    if (!isRoundDone && !rounds.isEmpty() && zombieCount <= 0)
    {
        isRoundDone = true;
        time = 0;//重置计时器
    }
    //播放僵尸来袭音乐
    if (isFirstRound && time+1 >= duration * 3/4)
    {
        QMediaPlayer* sound = new QMediaPlayer(this);
        sound->setMedia(QUrl::fromLocalFile("./sound/awooga.mp3"));
        sound->setVolume(musicVolume);
        sound->play();
        QGraphicsScene* catchScene = scene;
        mapScenes[catchScene].count++;
        QTimer::singleShot(4000, [sound, catchScene]()
            {
                if (mapScenes[catchScene].isValid != false)
                {
                    delete sound;
                    mapScenes[catchScene].count--;
                }
                else
                {
                    if (mapScenes[catchScene].count)
                    {
                        mapScenes[catchScene].count--;
                    }
                    if (mapScenes[catchScene].count == 0)
                    {
                        mapScenes.erase(catchScene);
                    }
                }
            });
        isFirstRound = false;
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
                int num = round[key] * difficultyIndex(Difficulty);//获取本轮键值僵尸的个数
                qInfo() << "num:" << num<<"Dif"<<Difficulty;
                while (num)
                {
                    //放僵尸
                    int offsetX = qrand() % 80;
                    int randRoad = qrand() % 5;
                    zombie* zombie = nullptr;
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
                    else if (key == "gargantuar")
                    {
                        zombie = new gargantuarzombie;
                    }
                    else if (key == "flag")
                    {
                        zombie = new flagzombie;
                    }
                    else if (key == "small")
                    {
                        zombie = new smallzombie;
                    }
                    else if (key == "yeti")
                    {
                        zombie = new yetizombie;
                    }
                    else if (key == "icetracker")
                    {
                        zombie = new icetrackerzombie;
                    }
                    else if (key == "apolo")
                    {
                        zombie = new apolozombie;
                    }
                    else if (key == "cleopatra")
                    {
                        zombie = new cleopatrazombie;
                    }
                    else if (key == "pharaoh")
                    {
                        zombie = new pharaohzombie;
                    }
                    else if (key == "pyramid")
                    {
                        zombie = new pyramidzombie;
                    }

                    if(zombie)zombie->setPos(988 + offsetX, 120 + 95 * randRoad);
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
    this->show();
    emit resumeLoadingBGM();
}

void adventureGameMode::bgmPlay()
{
    //开场特效
    QGraphicsScene* catchScene = scene;
    QPushButton* menu = menuButton;
    QLabel* gameReady = new QLabel();
    gameReady->setStyleSheet("background: transparent;"
                             "background-image: url(./images/StartReady.png);"
        " background-position: center;"
                             "background-repeat: no-repeat;"
                            );
    QTimer::singleShot(2000 / 3, [gameReady]() 
        {
            gameReady->setStyleSheet("background: transparent;"
                "background-image: url(./images/StartSet.png);"
                " background-position: center;"
                "background-repeat: no-repeat;"
            );
        });
    QTimer::singleShot(4000 / 3, [gameReady, catchScene,menu]()
        {
            gameReady->setStyleSheet("background: transparent;"
                "background-image: url(./images/StartPlant.png);"
                " background-position: center;"
                "background-repeat: no-repeat;"
            );
            QTimer::singleShot(800,[gameReady, catchScene,menu]()
                {
                    if (mapScenes[catchScene].isValid != false)
                    {
                        menu->setEnabled(true);
                        delete gameReady;
                        mapScenes[catchScene].count--;
                    }
                    else
                    {
                        if (mapScenes[catchScene].count)
                        {
                            mapScenes[catchScene].count--;
                        }
                        if (mapScenes[catchScene].count == 0)
                        {
                            mapScenes.erase(catchScene);
                        }
                    }
                });
        });
    gameReady->setGeometry(0, 0, scene->width(), scene->height());
    scene->addWidget(gameReady);
    QMediaPlayer* soundBegin = new QMediaPlayer(this);
    soundBegin->setMedia(QUrl::fromLocalFile("./sound/readysetplant.mp3"));
    soundBegin->setVolume(musicVolume);
    soundBegin->play();
    mapScenes[catchScene].count++;
    QTimer::singleShot(4100, [soundBegin, catchScene]()
        {
            if (mapScenes[catchScene].isValid != false)
            {
                delete soundBegin;
                mapScenes[catchScene].count--;
            }
            else
            {
                if (mapScenes[catchScene].count)
                {
                    mapScenes[catchScene].count--;
                }
                if (mapScenes[catchScene].count == 0)
                {
                    mapScenes.erase(catchScene);
                }
            }
        });
    //背景音乐
    gamingBGM = new(QMediaPlayer);
    gamingBGM_List = new(QMediaPlaylist);
    // 添加MP3文件到播放列表
    if (adventureGameMode::level < 6)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/04Grasswalk.mp3"));
    else if (adventureGameMode::level >= 6 && adventureGameMode::level <= 7)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/06Moongrains.mp3"));
    else if (adventureGameMode::level >= 8 && adventureGameMode::level <= 10)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/11RigorMormist.mp3"));
    else if (adventureGameMode::level >= 11 && adventureGameMode::level <= 13)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/09WaterGraves.mp3"));
    else if (adventureGameMode::level >= 14 && adventureGameMode::level <= 15)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/ZombiesOnYourLawn.mp3"));
    else if (adventureGameMode::level >= 16 && adventureGameMode::level <= 20)
        gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/13Grazetheroof.mp3"));
    // 设置播放模式为循环播放
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // 将播放列表设置给播放器
    gamingBGM->setPlaylist(gamingBGM_List);
    //设置音量
    gamingBGM->setVolume(musicVolume);
    // 开场音效完毕后开始播放音乐
    TimerThread* TimerT = mQTimer;
    QMediaPlayer* gBGM = gamingBGM;
    QTimer::singleShot(2100, [TimerT,gBGM]
    {
            gBGM->play();
            TimerT->start();
    });
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
    menuButton->setEnabled(false);
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
        mQTimer->stop();
        delete back;
        delete gamingBGM;
        delete gamingBGM_List;
        delete mQTimer;
        mapScenes[scene].isValid = false;
        delete scene;
    }
    delete view;
}

void adventureGameMode::getGamingMenu(gamingMenuDialog* gM) {
    gamingMenu = gM;
}