#include<qdebug.h>
#include "game.h"

game::game(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(910, 610);  
    mQTimer=new QTimer(this);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(150,0,900,600);//����img��Ҫ��ȡ����
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //��ͼ��ʾ�����꣬ע�����е����궼�ǻ���δ���ü�ͼƬ������
    //(290,120,10,10);(1,1)����(��������)
    //245,175->330,270->>>>����85 95
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
        Mower *mower = new Mower;//����������
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }
    //bgm����
    bgmPlay();
    // ������ͼ������������
    view = new QGraphicsView(scene, this);
    view->resize(905, 605);//���û��ƴ��ڴ�С
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // ���ñ���ͼƬ
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //������ť�ȿؼ���Ⱦ
    QPushButton*menuButton = new QPushButton;// �����˵���ť
    menuButton->setFixedSize(136, 36); // ���ð�ť��С

    // ���ð�ť����ʽ��������ͨ״̬����ͣ״̬�µı���ͼƬ
    menuButton->setStyleSheet("QPushButton {"
        "    border-image: url(:/new/prefix1/gamingMenu.png);"
        "}"
        "QPushButton:hover {"
        "    border-image: url(:/new/prefix1/gamingMenu1.png);"
        "}");

    // ���˵���ťǶ�뵽 QGraphicsProxyWidget
    QGraphicsProxyWidget* gamingWidgetsProxy = scene->addWidget(menuButton);
    gamingWidgetsProxy->setPos(894, 0); // ���ð�ť�ڳ����е�λ��

    // ���˵���ť��ӵ�����
    scene->addItem(gamingWidgetsProxy);
    //���Ӳ˵���ť
    connect(menuButton, &QPushButton::clicked, this, &game::goToGamingMenu);
    // ���Ӽ�ʱ����timeout�źŵ�������advance�ۣ�ʵ�ֳ���������Ķ���Ч��
    connect(mQTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    // ���Ӽ�ʱ����timeout�źŵ���Ϸ��addZombie�ۣ���ӽ�ʬ
    connect(mQTimer, &QTimer::timeout, this, &game::addZombie);
    // ���Ӽ�ʱ����timeout�źŵ���Ϸ��check�ۣ������Ϸ�Ƿ����
    connect(mQTimer, &QTimer::timeout, this, &game::checkGameState);
    mQTimer->start(33 / fpsIndex); // ������ʱ����(33 / fpsIndex)ÿ���봥��һ��timeout�źţ�������Ϸ����Ч��
    //qInfo() << "qTimer:" << mQTimer->interval();
    view->show(); // ��ʾ��ͼ
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
    static int maxtime = 20 * 1000 / (33 / fpsIndex);//��ʼ������ʬ���ʱ��
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        low++;
        if (low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }//������Ϸʱ��������߽�ʬ����Ƶ��
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
    // ��Ӷ��MP3�ļ��������б�
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/20. Grasswalk IN-GAME.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/13. Graze the Roof.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/06. Moongrains.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/09. Watery Graves (fast).mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/12. Cerebrawl.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/11. Rigor Mormist.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/05. Loonboon.mp3"));
    gamingBGM_List->addMedia(QUrl::fromLocalFile("./sound/14. Brainiac Maniac.mp3"));
    // ���ò���ģʽΪѭ������
    gamingBGM_List->setPlaybackMode(QMediaPlaylist::Loop);
    // �������б����ø�������
    gamingBGM->setPlaylist(gamingBGM_List);
    
    // �����������
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    // ���ѡȡһ�����ֽ��в���
    int index = qrand() % gamingBGM_List->mediaCount(); // ���������������
    qDebug() << "Initial song index:" << index;
    gamingBGM_List->setCurrentIndex(index); // ���õ�ǰ��������
    
    // ��ʼ��������
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
    //�����Ϸ�Ƿ�������Ƿ��н�ʬ������Ļ�����
    const QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem * item, items)
    {
        if (item->type() == zombie::Type && item->x() < 150)
        {
            //����н�ʬ������Ļ����ߣ���Ϸ����
            scene->addPixmap(QPixmap(":/new/prefix1/ZombiesWon.png"))->setPos(336, 92);
            scene->advance();
            mQTimer->stop(); //������ʱ��ֹͣ��Ϸ
            return;
        }
    }
}