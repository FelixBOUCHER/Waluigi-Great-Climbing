#include "powerup.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "game.h"

extern Game * game;

Powerup::Powerup(int min, int max, int type, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    int random_number = rand() % max + min;
    setPos(random_number, 0);

    if(type == 1) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Powerups/Yoshi_Slippers.png"));
    if(type == 2) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Powerups/The_Gharlic.png"));
    if(type == 3) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Powerups/Wario_Mustache_Cream.png"));
    if(type == 4) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Powerups/WAHll_Gloves.png"));
    setTransformOriginPoint(50,50);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));

    timer->start(2);

}

void Powerup::fall()
{
    setPos(x(),y()+0.8);

    if (y() > 1200)
    {
        scene()->removeItem(this);
        delete this;
    }
}
