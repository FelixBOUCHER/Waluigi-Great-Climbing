#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Waluigi.h"

class Game: public QGraphicsView
{

public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Waluigi * WAH;

};

#endif // GAME_H
