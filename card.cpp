#include "card.h"
#include "shop.h"
#include"gameIndex.h"

QMap<QString, CardsData> card::baseCardMap;
QMap<QString, CardsData> card::cardSelectedMap;

card::card(QString cardName)
{
    text = cardName;
    counter = 0;
}

QRectF card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}

void card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//����Ϸ�л��ƿ�Ƭ
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.6, 0.58);
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/new/prefix1/Card.png"));
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/new/prefix1/" + text + ".png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(-30, 60, QString("%1").arg(cardSelectedMap[text].cost, 3, 10, QChar(' ')));
    if (counter < cardSelectedMap[text].cool)
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cardSelectedMap[text].cool)));
    }
}

void card::advance(int phase)
{
    //qInfo() << "card:" << fpsIndex;
    if (!phase)
        return;
    update();
    if (counter < cardSelectedMap[text].cool)
        ++counter;
}

void card::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event)

        // �����Ƭ��ȴ�У��ܾ�����¼�
        if (counter < cardSelectedMap[text].cool) {
            qDebug() << "Card is cooling down";
            event->setAccepted(false);
            return; // Add a return here to ensure the event is not further processed
        }

    // ��ȡ��Ƭ������shop �ࣩ������������Ƿ��㹻����Ƭ
    shop* sh = qgraphicsitem_cast<shop*>(parentItem());
    if (cardSelectedMap[text].cost > sh->sunnum) {
        qDebug() << "Not enough sun points";
        event->setAccepted(false);
        return; // Add a return here to ensure the event is not further processed
    }

    // �������ָ��ΪĬ�ϼ�ͷ��״
    setCursor(Qt::ArrowCursor);
}

void card::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Mouse move event triggered";

    // ����Ƿ�������ק������
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())
        return;

    // ������ק����
    QDrag* drag = new QDrag(event->widget());
    QMimeData* mime = new QMimeData;
    QImage image(":/new/prefix1/" + text + ".png");
    mime->setText(text);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();

    // �������ָ��ΪĬ�ϼ�ͷ��״
    setCursor(Qt::ArrowCursor);
}

void card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event)

        // �������ָ��ΪĬ�ϼ�ͷ��״
        setCursor(Qt::ArrowCursor);
}