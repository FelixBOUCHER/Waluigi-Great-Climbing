#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include <QList>
#include <typeinfo>
#include <QGraphicsScene>
#include <iostream>

using namespace std;

Bullet::Bullet(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Garlic.png"));

    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(2);
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    setPos(x()+1,y()+0.4f);
    stamina--;

    /*for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
            cerr << colliding_items[i] << endl;
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
    }*/

    if(stamina <= 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
