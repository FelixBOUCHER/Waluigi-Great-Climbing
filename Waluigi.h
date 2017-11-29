#ifndef WALUIGI_H
#define WALUIGI_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Waluigi: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Waluigi(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void Init(int X, int Y);

public slots:
    void timing();
    void timbullet();
    void spawn();
    void THE_GREAT_WAH();
    void Ending();

private:
    bool imput[6] = {false};
    bool reload = true;

    bool firstjump = true;
    bool doublejump = true;

    float positionX, positionY;     // Position of the character
    float velocityX, velocityY;     // Velocity of the character
    float cap_velocityX = 1.25f;
    float cap_velocityY;
    float gravity = 0.04f;


    bool Safety_Protocol = true;
    bool Yoshi_Slippers = false;
    bool Gharlic = false;
    bool WarioCorp_Stache_Wax = false;
    bool SpaceRift_Overalls = false;
    bool WAHll_Gloves = false;
};

#endif
