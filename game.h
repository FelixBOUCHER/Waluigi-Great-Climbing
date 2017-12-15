#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Waluigi.h"
#include "wall.h"

class Game: public QGraphicsView
{

public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Waluigi * WAH;
    Wall * Left_Wall;
    Wall * Right_Wall;
};

#endif // GAME_H
