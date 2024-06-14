//utf8
#pragma once
#include "plant.h"

class BowlingNut : public plant
{
public:
    BowlingNut(); // 构造函数，创建一个保龄球对象，attack表示攻击力
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override; // 判断豌豆是否与其他图形项发生碰撞
    void advance(int phase) override; // 控制保龄球的移动和攻击逻辑
private:
    int atk; // 攻击力
    qreal speed; // 速度（每秒移动的像素数）
};

