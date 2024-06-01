#include "survivalMode.h"

survivalGameMode::survivalGameMode(QWidget* parent)
    : QWidget{ parent }, mQTimer(new HighPrecisionTimer(this)), view(nullptr), scene(nullptr), gamingMenu(nullptr),
gamingBGM(nullptr), gamingBGM_List(nullptr) 
{   
    initIndex();
    /* �������� */
    this->setFixedSize(910, 610);

    // ʹ�ø߾��ȶ�ʱ��
    mQTimer = new HighPrecisionTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600); // ����img��Ҫ��ȡ����
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // ��ʼ��������������ֲ��䣩
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
        Mower* mower = new Mower; // ����������
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    // bgm����
    bgmPlay();
    // ������ͼ������������
    view = new QGraphicsView(scene, this);
    view->resize(905, 605); // ���û��ƴ��ڴ�С
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // ���ñ���ͼƬ
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    // ������ť�ȿؼ���Ⱦ
    createMenuButton();
    // ���Ӳ˵���ť
    connect(menuButton, &QPushButton::clicked, this, &survivalGameMode::goToGamingMenu);
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ�������advance�ۣ�ʵ�ֳ���������Ķ���Ч��
    connect(mQTimer, &HighPrecisionTimer::timeout, scene, &QGraphicsScene::advance);
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ���Ϸ��addZombie�ۣ���ӽ�ʬ
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &survivalGameMode::addZombie);
    // ���Ӹ߾��ȶ�ʱ����timeout�źŵ���Ϸ��check�ۣ������Ϸ�Ƿ����
    connect(mQTimer, &HighPrecisionTimer::timeout, this, &survivalGameMode::checkGameState);
    mQTimer->start(33333 / fpsIndex); // �����߾��ȶ�ʱ������΢��Ϊ��λ
    qInfo() << "High precision timer started with interval:" << 33333 / fpsIndex << " microseconds";
    view->show(); // ��ʾ��ͼ
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
        }//������Ϸʱ��������߽�ʬ����Ƶ��
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
    // ��Ӷ��MP3�ļ��������б�
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/04Grasswalk.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/05LoonBoon.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/06Moongrains.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/09WaterGraves.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/11RigorMormist.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/12cerebrawl.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/14BrainiacManiac.mp3"));
    // ���ò���ģʽΪѭ������
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // �������б����ø�������
    gamingBGM->setPlaylist(gamingBGM_List);

    // �����������
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    // ���ѡȡһ�����ֽ��в���
    int index = qrand() % gamingBGM_List->mediaCount(); // ���������������
    gamingBGM_List->setCurrentIndex(index); // ���õ�ǰ��������
    gamingBGM->setVolume(musicVolume);
    // ��ʼ��������
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
    maxtime = 20 * fpsIndex * 1000000 / 33333;//��ʼ������ʬ���ʱ��
    time = maxtime / 2;
    counter = 0;
}

void survivalGameMode::createMenuButton()
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

void survivalGameMode::checkGameState()
{
    //�����Ϸ�Ƿ�������Ƿ��н�ʬ������Ļ�����
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
    {
        if (item->type() == zombie::Type && item->x() < 150)
        {
            // ������ʱ��ֹͣ��Ϸ
            mQTimer->stop();

            // �����Ϸ����ͼƬ
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
            connect(gameOverButton, &QPushButton::clicked,this,&survivalGameMode::gameOver );

        }
    }
}