#ifndef SHOP_H
#define SHOP_H

#include "other.h"
#include "plant.h"
#include "card.h"
#include "sun.h"
#include "sunflower.h"
#include "pea.h"
#include "cherry.h"
#include "wallnut.h"
#include "snowpea.h"
#include "potato.h"
#include "DoublePea.h"
#include"Jalapeno.h"
#include"GatlingPea.h"
#include"FumeShroom.h"
#include"PuffShroom.h"
#include"GloomShroom.h"
#include"SunShroom.h"
#include"Torchwood.h"
#include"TwinSunflower.h"
#include"gameIndex.h"

class shop : public other
{
public:
    int sunnum;//��ǰ������
    shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addPlant(QString s, QPointF pos);//���ֲ��
private:
    int counter;
    int time;
};

#endif // SHOP_H
