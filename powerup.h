#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Powerup: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Powerup(int min, int max, int type, QGraphicsItem * parent=0);
public slots:
    void fall();
};
#endif // POWERUP_H
