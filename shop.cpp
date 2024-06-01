#include "shop.h"
shop::shop()
{
    sunnum = 200;
    counter = 0;
    time = int(10.0 * 1000000 * (double)fpsIndex / 33333 );
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
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() == plant::Type)
            return;
    sunnum -= card::card::baseCardMap[s].cost;
    plant *pl = nullptr;
    QString cardName = card::baseCardMap[s].name;

    if (cardName == "SunFlower") {
        pl = new sunflower;
    }
    else if (cardName == "Peashooter") {
        pl = new pea;
    }
    else if (cardName == "CherryBomb") {
        pl = new cherry;
    }
    else if (cardName == "WallNut") {
        pl = new wallnut;
    }
    else if (cardName == "SnowPea") {
        pl = new snowpea;
    }
    else if (cardName == "PotatoMine") {
        pl = new potato;
    }
    else if (cardName == "DoublePea") {
        pl = new DoublePea;
    }
    else if (cardName == "GatlingPea") {
        pl = new GatlingPea;
    }
    else if (cardName == "Jalapeno") {
        pl = new Jalapeno;
    }
    else {
        // 处理未知的植物类型
        qWarning() << "Unknown plant type:" << cardName;
    }
    pl->setPos(pos);
    scene()->addItem(pl);
    QList<QGraphicsItem *> child = childItems();
    foreach (QGraphicsItem *item, child)
    {
        card *car = qgraphicsitem_cast<card *>(item);
        if (car->text == s)
            car->counter = 0;
    }
    counter = 0;
}

