#include "card.h"
#include "shop.h"
#include"gameIndex.h"
 QMap<QString, int> card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},
                                     {"SnowPea", 4}, {"PotatoMine", 5}, {"Repeater", 6}};
 QVector<QString> card::name = {"SunFlower", "Peashooter", "CherryBomb", "WallNut",
                                     "SnowPea", "PotatoMine", "Repeater"};
 QVector<int> card::cost = { 50, 100, 150, 50, 175, 25, 200 };
 QVector<int> card::cool = { 227 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex, 606 * fpsIndex, 227 * fpsIndex };//���ÿ�Ƭ��ȴʱ��

card::card(QString cardName)
{
    text = cardName;
    counter = 0;
}

QRectF card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}

void card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.6, 0.58);
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/new/prefix1/Card.png"));
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/new/prefix1/" + text + ".png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(-30, 60, QString("%1").arg(cost[map[text]], 3, 10, QChar(' ')));
    qInfo() << "counter:" << counter << "cool" << cool[map[text]];
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }
}

void card::advance(int phase)
{
    //qInfo() << "card:" << fpsIndex;
    if (!phase)
        return;
    update();
    if (counter < cool[map[text]])
        ++counter;
}

void card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (counter < cool[map[text]])
        event->setAccepted(false);
    shop *sh = qgraphicsitem_cast<shop *>(parentItem());
    if (cost[map[text]] > sh->sunnum)
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);//Ĭ�ϵ����ָ����״
}

void card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())//���������¼��������յ�֮��ľ����Ƿ�С��ϵͳ���õĿ�ʼ��ק�ľ�����ֵ��
        //����Ϊ�˷�ֹ�ڵ��ʱ���ⴥ����ק������
        return;
    QDrag *drag = new QDrag(event->widget());//����һ���µ���ק����QDrag���ö�������ʵ����ק������
    QMimeData *mime = new QMimeData;//���ڴ洢Ҫ��ק�����ݡ�
    QImage image(":/new/prefix1/" + text + ".png");
    mime->setText(text);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();//ִ����ק��������ʼ��ק��
    setCursor(Qt::ArrowCursor);
}

void card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
