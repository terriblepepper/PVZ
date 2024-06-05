#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include<QTimer>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include <QMovie>

class zombie : public QGraphicsItem
{
public:
    enum { Type = UserType + 2};
    double hp;
    int state;
    double atk;
    qreal speed;
    QMovie* mQMovie;
    QMovie* mhead;
    QMediaPlayer* zmSound;
    QMediaPlaylist* zmSoundList;
    bool isSnow;
    zombie();
    ~zombie();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )override;
    QRectF boundingRect()const override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void setMovie(QString path);
    void setHead(QString path);
    int type()const override;

};

#endif // ZOMBIE_H
