#include "wall.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include <time.h>

//extern Game * game;

Wall::Wall(int x, int y, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPos(x, y);
    setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/The_WAHll.png"));
}
