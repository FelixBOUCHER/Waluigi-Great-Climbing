#include "Waluigi.h"
#include "enemy.h"
#include "platform.h"
#include "powerup.h"
#include "bullet.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <QPixmap>

using namespace std;

QTimer * timer = new QTimer();

Waluigi::Waluigi(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi.png"));

    QTimer *beat = new QTimer;
    connect(beat,SIGNAL(timeout()),this,SLOT(timing()));

    QTimer *reloading = new QTimer;
    connect(reloading,SIGNAL(timeout()),this,SLOT(timbullet()));

    QTimer *End_of_Safety = new QTimer;
    connect(End_of_Safety,SIGNAL(timeout()),this,SLOT(Ending()));

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(1000);

    beat->start(2);
    reloading->start(600);
    End_of_Safety->start(6000);

}

void Waluigi::Init(int X, int Y)
{
    cerr << X << " " << Y << endl;
    positionX = X;
    positionY = Y;

    velocityX = 0;
    velocityY = 0;
}

void Waluigi::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    if (key == Qt::Key_Left) {e->accept(); imput[0] = true;}
    if (key == Qt::Key_Right) {e->accept(); imput[1] = true;}
    if (key == Qt::Key_Up)
    {
        if(firstjump == true || (doublejump == true && Yoshi_Slippers == true))
        {
            velocityY = -4.2f;

            if(firstjump == true)
            {
                firstjump = false;
            }

            else doublejump = false;
        }
    }

    if (key == Qt::Key_Space)
    {
        if(reload == true)
        {
            Bullet *bullet = new Bullet();
            bullet->setPos(positionX, positionY+100);
            scene()->addItem(bullet);
            reload = false;
        }
    }
}

void Waluigi::keyReleaseEvent(QKeyEvent *e)
{
    int key = e->key();

    if (key == Qt::Key_Left) {e->accept(); imput[0] = false;}
    if (key == Qt::Key_Right) {e->accept(); imput[1] = false;}
}

void Waluigi::timing()
{
    if (imput[0] == true) { setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi_L.png")); if(abs(velocityX) < cap_velocityX) velocityX -= 0.1f;}
    if (imput[1] == true) { setPixmap(QPixmap("/auto_home/fboucher/WAH_Maker/images/Waluigi.png")); if(abs(velocityX) < cap_velocityX) velocityX += 0.1f;}

    positionX += velocityX;   // Apply horizontal velocity to X position
    positionY += velocityY;   // Apply vertical velocity to X position
    velocityY += gravity;     // Apply gravity to vertical velocity

    setPos(positionX,positionY);

    if(velocityX > 0) velocityX -= 0.03f;
    if(velocityX < 0) velocityX += 0.03f;

    if(velocityX > 0 && velocityX < 0.03) velocityX = 0;
    if(velocityX < 0 && velocityX > -0.03) velocityX = 0;

    QList<QGraphicsItem *> colliding_items = collidingItems();
    int grounded = 900;
    bool heigh = false;

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid(*(colliding_items[i])) == typeid(Platform))
        {
            if(positionY+100 - colliding_items[i]->y() <= 15.f && positionY+100 - colliding_items[i]->y() >= -15.f && velocityY >= 0.2f)
            {
                grounded = colliding_items[i]->y()-100;
                heigh = true;
            }

            else if(velocityY <= -0.1f && Gharlic == false)
            {
                velocityY = 0;
                velocityX = 0;
            }
        }

        if(typeid(*(colliding_items[i])) == typeid(Powerup))
        {
            if(Yoshi_Slippers == false) Yoshi_Slippers = true;
            else if(Gharlic == false) Gharlic = true;
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
    }

    if(heigh == true)
        {
            positionY = grounded;
            velocityY = 0.0;
            firstjump = true;
            doublejump = true;
        }

    else if(Safety_Protocol == true && positionY > 900)
        {
            positionY = 900;
            velocityY = 0.0;
            firstjump = true;
            doublejump = true;
        }
}

void Waluigi::timbullet()
{
    reload = true;
}

void Waluigi::Ending()
{
    Safety_Protocol = false;
}

void Waluigi::spawn()
{
    if(Gharlic == true)
    {
        timer->setInterval(1500);
        Platform * enemy = new Platform(0, 800, 0.5, 3);
        scene()->addItem(enemy);
    }
    else if(Yoshi_Slippers == true)
    {
        Platform * enemy = new Platform(0, 800, 0.4, 2);
        scene()->addItem(enemy);
    }
    else
    {
        Platform * enemy = new Platform(0, 300, 0.4, 1);
        Platform * enemy2 = new Platform(500, 800, 0.4, 1);
        scene()->addItem(enemy);
        scene()->addItem(enemy2);
    }
}

void Waluigi::THE_GREAT_WAH()
{
    if(Yoshi_Slippers == false)
    {
        Powerup * P = new Powerup(250, 750, 1);
        scene()->addItem(P);
    }

    if(Yoshi_Slippers == true && Gharlic == false)
    {
        Powerup * P = new Powerup(0, 1000, 2);
        scene()->addItem(P);
    }
}


