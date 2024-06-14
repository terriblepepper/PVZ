#pragma once
#include "other.h"
class smallBubble : public other
{
public:
    smallBubble(int attack = 0, bool flag = false); // 构造函数，创建一个豌豆对象，attack表示攻击力，flag表示是否带有冰冻效果，默认为0和false
    QRectF boundingRect() const override; // 返回豌豆的边界矩形，用于碰撞检测
    bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override; // 判断豌豆是否与其他图形项发生碰撞
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override; // 绘制豌豆射手的外观
    void advance(int phase) override; // 控制豌豆的移动和攻击逻辑
    int originX;//初始X坐标
private:
    double atk; // 攻击力
    qreal speed; //移动速度（每秒移动的像素数）
};