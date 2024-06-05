#include"shop.h"

shop::shop()
{
    sunnum = 250;
    counter = 0;
    card *card_name = nullptr;
    int i = 0;
    for (auto& key : card::cardSelectedMap.keys())
    {
        card_name = new card(key);
        card_name->setParentItem(this);
        card_name->setPos(-157 + 65 * i++, -2);
    }
}

QRectF shop::boundingRect() const
{
    return QRectF(-270, -45, 540, 90);
}

void shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/new/prefix1/Shop.png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sunnum));//显示阳光
}

void shop::advance(int phase)
{
    time = (int)((qrand() % 30 + 5) * 1000000. / (33333. / (double)fpsIndex));//将生产阳光时间随机化
    if (!phase)
        return;
    update();
    if (++counter >= time)//添加阳光
    {
        counter = 0;
        scene()->addItem(new sun);
    }
}

void shop::addPlant(QString s, QPointF pos)//在游戏中添加植物
{
    QList<QGraphicsItem *> items = scene()->items(QRectF(pos.x() - 22.5 / 2, pos.y() - 27.5 / 2, 22.5, 27.5));
    int countAround = 0;
    foreach(QGraphicsItem * item, items) 
    {
        if (item->type() == plant::Type)
        {
            countAround++;
            plant* p = dynamic_cast<plant*>(item);
            if (!judgeAdd(s, pos, p))
                return;
        }       
    }
    if (countAround <= 0 && adventureGameMode::level < 21 && adventureGameMode::level>15 && s != "Pot")
        return;

    sunnum -= card::card::cardSelectedMap[s].cost;
    plant *pl = nullptr;
    QString cardName = card::cardSelectedMap[s].name;

    if (cardName == "SunFlower") {
        pl = new sunflower;
    }
    else if (cardName == "Peashooter") 
    {
        pl = new pea;
    }
    else if (cardName == "CherryBomb") 
    {
        pl = new cherry;
    }
    else if (cardName == "WallNut") 
    {
        pl = new wallnut;
    }
    else if (cardName == "SnowPea") 
    {
        pl = new snowpea;
    }
    else if (cardName == "PotatoMine") 
    {
        pl = new potato;
    }
    else if (cardName == "DoublePea") 
    {
        pl = new DoublePea;
    }
    else if (cardName == "GatlingPea") 
    {
        pl = new GatlingPea;
    }
    else if (cardName == "Jalapeno") 
    {
        pl = new Jalapeno;
    }
    else if(cardName == "FumeShroom")
    {
        pl = new FumeShroom;
    }
    else if (cardName == "PuffShroom")
    {
        pl = new PuffShroom;
    }
    else if (cardName == "GloomShroom")
    {
        pl = new GloomShroom;
    }
    else if (cardName == "SunShroom")
    {
        pl = new SunShroom;
    }
    else if (cardName == "Torchwood")
    {
        pl = new Torchwood;
    }
    else if (cardName == "TwinSunflower") 
    {
        pl = new TwinSunflower;
    }
    else if (cardName == "CaiWen")
    {
        pl = new CaiWen;
        pos.setX(pos.x() - 10);
    }
    else if (cardName == "Pot")
    {
        pl = new Pot;
    }
    else if (cardName == "BowlingNut")
    {
        pl = new BowlingNut;
    }
    else 
    {
        // 处理未知的植物类型
        qWarning() << "Unknown plant type:" << cardName;
        return;
    }
    //处理种植越界问题
    if (pos.y() > 500)
        return;
    //处理pot的位置
    if (pl->isPot)
    {
        pos.setY(pos.y() + 20);
        pl->setPos(pos);
    }
    else
    {
        pl->setPos(pos);
    }
    QMediaPlayer* sound = new QMediaPlayer();
    sound->setMedia(QUrl::fromLocalFile("./sound/plant.mp3"));
    sound->setVolume(itemVolume);
    sound->play();
    QGraphicsScene* catchScene = scene();
    mapScenes[catchScene].count++;
    mapScenes[catchScene].soundsCount++;
    connect(sound, &QMediaPlayer::stateChanged, [sound, catchScene](QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState) {
            if (mapScenes[catchScene].isValid != false) {
                delete sound;
                mapScenes[catchScene].count--;
                mapScenes[catchScene].soundsCount--;
                return;
            }
            else {
                if (mapScenes[catchScene].count) {
                    mapScenes[catchScene].count--;
                }
                if (mapScenes[catchScene].count == 0) {
                    mapScenes.erase(catchScene);
                }
            }
        }
        });
    scene()->addItem(pl);
    qInfo() << "pos: " << pos;
    QList<QGraphicsItem *> child = childItems();
    foreach (QGraphicsItem *item, child)
    {
        card *car = qgraphicsitem_cast<card *>(item);
        if (car->text == s)
            car->counter = 0;
    }
    counter = 0;
}

bool shop::judgeAdd(QString s, QPointF &pos, plant* p)
{
    
    if (p->isPot && s != "Pot")
    {
        pos.setY(pos.y() - 10);
        return true;
    }
    return false;
}
