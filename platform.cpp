#include "platform.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include <time.h>
#include "game.h"

extern Game * game;

Platform::Platform(int min, int max, float F, int type, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    srand (time(NULL));
    int random_number = rand() % max + min;
    setPos(random_number, 0);

    if(type == 1) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi_platform_long.png"));
    if(type == 2) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi_platform_medium.png"));
    if(type == 3) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi_platform_short.png"));
    if(type == 4) setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi_platform_mini.png"));
    setTransformOriginPoint(50,50);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));

    fallspeed = F;

    timer->start(2);
}

void Platform::fall()
{
    setPos(x(),y()+fallspeed);

    if (y() > 1200)
    {
        scene()->removeItem(this);
        delete this;
    }
}
