#include "game.h"
#include "enemy.h"
#include "Waluigi.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent){

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1600,1200);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1600,1200);

    WAH = new Waluigi();
    WAH -> Init(800,900);
    WAH -> setFlag(QGraphicsItem::ItemIsFocusable);
    WAH -> setFocus();
    scene -> addItem(WAH);

    QTimer * timer_WAH = new QTimer();
    QObject::connect(timer_WAH,SIGNAL(timeout()),WAH,SLOT(THE_GREAT_WAH()));
    timer_WAH->start(8000);

    show();
}
