#include "smallgameMode.h"

int smallGameMode::level = 0;
smallGameMode::smallGameMode(QWidget* parent) : QWidget(parent) {
    setupUi();
    setFixedSize(910, 610);
    setWindowTitle("PlantsVsZombies");
    setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // 设置窗口图标
}

void smallGameMode::goToGamingMenu()
{
    mQTimer->pause();
    gamingBGM->pause();
    gamingMenu->show();
}

bool smallGameMode::loadLevelConfig(const QString& filePath, QQueue<QMap<QString, int>>& waves)
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

void smallGameMode::setupUi() {
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
    connect(this->back, &QPushButton::clicked, this, &smallGameMode::onBackClicked);
    mainLayout->addWidget(back);

    // 创建堆栈式窗口
    Widget = new QStackedWidget(this);
    // 创建关卡选择页面
    QWidget* levelWidget = new QWidget();
    QVBoxLayout* levelLayout = new QVBoxLayout(levelWidget);
    QPixmap backgroundPixmap(":/new/prefix1/levelSelectBackground.jpg");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    levelWidget->setStyleSheet("background-image: url(:/new/prefix1/levelSelectBackground.jpg);");

    // 添加关卡选择按钮
    for (int i = 1; i <= 20; ++i) {
        QPushButton* levelButton = new QPushButton;
        levelButton->setText("坚果保龄球：" + QString("关卡%1").arg(i));
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
            QString temp = levelButton->objectName();
            smallGameMode::level = temp.remove("level_").toInt();//按下关卡按钮就立马设置关卡
            emit stopLoadingBGM();
            startGame();
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

void smallGameMode::loadCards(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file" << filename;
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(data);

    if (document.isNull() || !document.isArray()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        CardsData card;
        card.name = obj["name"].toString();
        card.cool = obj["cool"].toInt();
        card.cost = obj["cost"].toInt();
        card::cardSelectedMap.insert(card.name, card);
    }
}

void smallGameMode::startGame() {
    setWindowTitle("PlantsVsZombies | miniGame");
    //初始化参数
    initIndex();
    loadCards("./configs/cardsMini.json");//加载卡片

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
    if (smallGameMode::level < 6)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    else if (smallGameMode::level > 5 && smallGameMode::level < 11)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background2.jpg")); // 设置背景图片
    else if (smallGameMode::level > 10 && smallGameMode::level < 16)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background3.jpg")); // 设置背景图片
    else if (smallGameMode::level > 15 && smallGameMode::level <= 20)
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
    connect(mQTimer, &HighPrecisionTimer::timeout, scene, &QGraphicsScene::advance);
    // 连接高精度定时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &smallGameMode::addZombie);
    // 连接高精度定时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &smallGameMode::checkGameState);
    mQTimer->start(33333 / fpsIndex); // 启动高精度定时器，以微秒为单位
    view->show();
    //添加菜单按钮
    createMenuButton();
    //连接到菜单按钮
    connect(menuButton, &QPushButton::clicked, this, &smallGameMode::goToGamingMenu);
}

void smallGameMode::initIndex()
{
    low = 1 * fpsIndex;
    high = 2 * fpsIndex;
    maxtime = 3 * fpsIndex * 1000000 / 33333;//初始最大出僵尸间隔时间
    time = maxtime / 2;
    counter = 0;
}

void smallGameMode::checkGameState()
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
    //坚持一定时间就胜利
    if ((double)timeCounter / (30 * fpsIndex) > 150. * (1. + (double)smallGameMode::level * 0.45))
    {
        winScene();
    }
}
//待修改
void smallGameMode::addZombie()
{
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
        int type = qrand() % 152;
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
        else if (type < 115)
            zombie = new flagzombie;
        else if (type < 125)
            zombie = new smallzombie;
        else if (type < 128)
            zombie = new yetizombie;
        else if (type < 130)
            zombie = new icetrackerzombie;
        else if (type < 135)
            zombie = new apolozombie;
        else if (type < 140)
            zombie = new cleopatrazombie;
        else if (type < 142)
            zombie = new pharaohzombie;
        else if (type < 152)
            zombie = new pyramidzombie;
        zombie->setPos(1028, 120 + 95 * i);
        scene->addItem(zombie);
    }
    timeCounter++;
}

void smallGameMode::bgmPlay()
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

void smallGameMode::createMenuButton()
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

void smallGameMode::failScene()
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
    connect(gameOverButton, &QPushButton::clicked, this, &smallGameMode::gameFinish);
}

void smallGameMode::winScene()
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
    connect(gameWinButton, &QPushButton::clicked, this, &smallGameMode::gameFinish);
}

smallGameMode::~smallGameMode()
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

void smallGameMode::getGamingMenu(gamingMenuDialog* gM) {
    gamingMenu = gM;
}

