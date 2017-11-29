#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Platform: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Platform(int min, int max, float fallspeed, int type, QGraphicsItem * parent=0);
public slots:
    void fall();

private:
    float fallspeed;
};


#endif // PLATFORM_H
