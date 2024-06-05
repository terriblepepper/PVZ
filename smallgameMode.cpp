#include "smallgameMode.h"

int smallGameMode::level = 0;
smallGameMode::smallGameMode(QWidget* parent) : QWidget(parent) {
    setupUi();
    setFixedSize(910, 610);
    setWindowTitle("PlantsVsZombies");
    setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // ���ô���ͼ��
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
    back = new QPushButton("����");
    back->setFixedSize(120, 40);
    back->move(790, back->y());
    back->setStyleSheet("QPushButton {"
        "border-image: url(:/new/prefix1/levelbutton.png) center no-repeat;" // ���ð�ť��ʽ����������ͼƬ
        "font-size: 30px;" // ���������С
        "font-weight: bold"
        "}"
        "QPushButton:hover {" // �����ͣ��ʽ
        "color: green;" // ���������ͣʱ��������ɫ
        "border-image: url(:/new/prefix1/levelbutton1.png) center no-repeat;"
        "}");
    connect(this->back, &QPushButton::clicked, this, &smallGameMode::onBackClicked);
    mainLayout->addWidget(back);

    // ������ջʽ����
    Widget = new QStackedWidget(this);
    // �����ؿ�ѡ��ҳ��
    QWidget* levelWidget = new QWidget();
    QVBoxLayout* levelLayout = new QVBoxLayout(levelWidget);
    QPixmap backgroundPixmap(":/new/prefix1/levelSelectBackground.jpg");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    levelWidget->setStyleSheet("background-image: url(:/new/prefix1/levelSelectBackground.jpg);");

    // ��ӹؿ�ѡ��ť
    for (int i = 1; i <= 20; ++i) {
        QPushButton* levelButton = new QPushButton;
        levelButton->setText("���������" + QString("�ؿ�%1").arg(i));
        //����button�Ĺ�������
        levelButton->setObjectName(QString("level_%1").arg(i));
        levelButton->setFixedHeight(80);
        levelButton->setStyleSheet("QPushButton {"
            "border-image: url(:/new/prefix1/levelbutton.png) center no-repeat;" // ���ð�ť��ʽ����������ͼƬ
            "font-size: 30px;" // ���������С
            "font-weight: bold"
            "}"
            "QPushButton:hover {" // �����ͣ��ʽ
            "color: green;" // ���������ͣʱ��������ɫ
            "border-image: url(:/new/prefix1/levelbutton1.png) center no-repeat;"
            "}");
        connect(levelButton, &QPushButton::clicked, [this, levelButton]() {
            QString temp = levelButton->objectName();
            smallGameMode::level = temp.remove("level_").toInt();//���¹ؿ���ť���������ùؿ�
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
    // ������Ϸ��ͼ

    view = new QGraphicsView(this);
    view->setAlignment(Qt::AlignCenter);
    view->hide();  // ��ʼʱ������ͼ

    mainLayout->addWidget(Widget);
    setLayout(mainLayout); // ���ò��ֵ�adventureGameMode����
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
    //��ʼ������
    initIndex();
    loadCards("./configs/cardsMini.json");//���ؿ�Ƭ

    //����BGM
    bgmPlay();

    // ʹ�ø߾��ȶ�ʱ��
    mQTimer = new HighPrecisionTimer(this);
    // ������Ϸ������������ֱ���
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600); // ����img��Ҫ��ȡ����
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // ��ʼ���������
    shop* cardBar = new shop;
    cardBar->setPos(520, 45);
    scene->addItem(cardBar);

    shovel* sho = new shovel;
    sho->setPos(830, 40);
    scene->addItem(sho);

    Map* baseCardMap = new Map;
    baseCardMap->setPos(618, 326);
    scene->addItem(baseCardMap);

    // ������ͼ���Բ���������ӵ���ͼ��
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    if (smallGameMode::level < 6)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // ���ñ���ͼƬ
    else if (smallGameMode::level > 5 && smallGameMode::level < 11)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background2.jpg")); // ���ñ���ͼƬ
    else if (smallGameMode::level > 10 && smallGameMode::level < 16)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background3.jpg")); // ���ñ���ͼƬ
    else if (smallGameMode::level > 15 && smallGameMode::level <= 20)
        view->setBackgroundBrush(QPixmap(":/new/prefix1/Background4.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //��ӳ��ݻ�
    for (int i = 0; i < 5; ++i) {
        Mower* mower = new Mower;
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }

    // ������ͼ��С����ʾ
    view->resize(905, 605); // ȷ����ͼ��С�볡����Сƥ��
    view->move(0, 0); // ȷ����ͼ�ڴ����е�λ����ȷ
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ�������advance�ۣ�ʵ�ֳ���������Ķ���Ч��
    connect(mQTimer, &HighPrecisionTimer::timeout, scene, &QGraphicsScene::advance);
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ���Ϸ��addZombie�ۣ���ӽ�ʬ
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &smallGameMode::addZombie);
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ���Ϸ��check�ۣ������Ϸ�Ƿ����
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &smallGameMode::checkGameState);
    mQTimer->start(33333 / fpsIndex); // �����߾��ȶ�ʱ������΢��Ϊ��λ
    view->show();
    //��Ӳ˵���ť
    createMenuButton();
    //���ӵ��˵���ť
    connect(menuButton, &QPushButton::clicked, this, &smallGameMode::goToGamingMenu);
}

void smallGameMode::initIndex()
{
    low = 1 * fpsIndex;
    high = 2 * fpsIndex;
    maxtime = 3 * fpsIndex * 1000000 / 33333;//��ʼ������ʬ���ʱ��
    time = maxtime / 2;
    counter = 0;
}

void smallGameMode::checkGameState()
{
    //�����Ϸ�Ƿ�������Ƿ��н�ʬ������Ļ�����
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
    //���һ��ʱ���ʤ��
    if ((double)timeCounter / (30 * fpsIndex) > 150. * (1. + (double)smallGameMode::level * 0.45))
    {
        winScene();
    }
}
//���޸�
void smallGameMode::addZombie()
{
    if (++counter >= time)
    {
        low++;
        if (low > high)
        {
            maxtime /= 1.3;
            high *= 2.2;
        }//������Ϸʱ��������߽�ʬ����Ƶ��
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
    // ���MP3�ļ��������б�
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/04Grasswalk.mp3"));
    // ���ò���ģʽΪѭ������
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // �������б����ø�������
    gamingBGM->setPlaylist(gamingBGM_List);
    //��������
    gamingBGM->setVolume(musicVolume);
    // ��ʼ��������
    gamingBGM->play();

}

void smallGameMode::createMenuButton()
{
    menuButton = new QPushButton; // �����˵���ť
    menuButton->setFixedSize(136, 36); // ���ð�ť��С

    // ���ð�ť����ʽ��������ͨ״̬����ͣ״̬�µı���ͼƬ
    menuButton->setStyleSheet("QPushButton {"
        "    border-image: url(:/new/prefix1/gamingMenu.png);"
        "}"
        "QPushButton:hover {"
        "    border-image: url(:/new/prefix1/gamingMenu1.png);"
        "}");

    // ���˵���ťǶ�뵽 QGraphicsProxyWidget
    gamingWidgetsProxy = scene->addWidget(menuButton);
    gamingWidgetsProxy->setPos(894, 0); // ���ð�ť�ڳ����е�λ��
    // ���˵���ť��ӵ�����
    scene->addItem(gamingWidgetsProxy);
}

void smallGameMode::failScene()
{
    // ������ʱ��ֹͣ��Ϸ
    mQTimer->stop();
    // �����Ϸʧ�ܵĽ���ͼƬ
    scene->addPixmap(QPixmap(":/new/prefix1/ZombiesWon.png"))->setPos(336, 92);
    gamingBGM->stop();
    gamingBGM->setMedia(QUrl::fromLocalFile("./sound/losemusic.mp3"));
    gamingBGM->play();
    scene->advance();

    // ����һ��͸���� QPushButton ������������
    gameOverButton = new QPushButton();
    gameOverButton->setStyleSheet("background: transparent;");
    gameOverButton->setFlat(true);
    gameOverButton->setGeometry(0, 0, scene->width(), scene->height());

    // �� QPushButton ��ӵ�������
    gamingWidgetsProxy = scene->addWidget(gameOverButton);
    gamingWidgetsProxy->setPos(0, 0);
    connect(gameOverButton, &QPushButton::clicked, this, &smallGameMode::gameFinish);
}

void smallGameMode::winScene()
{
    // ������ʱ��ֹͣ��Ϸ
    mQTimer->stop();
    // �����Ϸʤ���Ľ���ͼƬ
    scene->addPixmap(QPixmap(":/new/prefix1/gameWin.png"))->setPos(336, 92);
    gamingBGM->stop();
    gamingBGM->setMedia(QUrl::fromLocalFile("./sound/winmusic.mp3"));
    gamingBGM->play();
    scene->advance();

    // ����һ��͸���� QPushButton ������������
    gameWinButton = new QPushButton();
    gameWinButton->setStyleSheet("background: transparent;");
    gameWinButton->setFlat(true);
    gameWinButton->setGeometry(0, 0, scene->width(), scene->height());

    // �� QPushButton ��ӵ�������
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

