#ifndef WALL_H
#define WALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Wall: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Wall(int x, int y, QGraphicsItem * parent=0);
    int WidthWall = 20;
};

#endif
