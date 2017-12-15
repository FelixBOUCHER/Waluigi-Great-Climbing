#include "Waluigi.h"
#include "enemy.h"
#include "wall.h"
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
#include <time.h>
#include <QPixmap>

using namespace std;

QTimer * timer = new QTimer();
QTimer *reloading = new QTimer;

Waluigi::Waluigi(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    Waluigi_Animation[1].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_L.png");
    Waluigi_Animation[2].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_1_L.png");
    Waluigi_Animation[3].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_2_L.png");
    Waluigi_Animation[4].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_3_L.png");
    Waluigi_Animation[5].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_4_L.png");
    Waluigi_Animation[6].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_5_L.png");
    Waluigi_Animation[7].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_jump_L.png");
    Waluigi_Animation[8].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi.png");
    Waluigi_Animation[9].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_1.png");
    Waluigi_Animation[10].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_2.png");
    Waluigi_Animation[11].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_3.png");
    Waluigi_Animation[12].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_4.png");
    Waluigi_Animation[13].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_5.png");
    Waluigi_Animation[14].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_numero_jump.png");
    Waluigi_Animation[15].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_Wallgrip_L.png");
    Waluigi_Animation[16].load("/auto_home/fboucher/WAH_Maker/images/Waluigi/Waluigi_Wallgrip.png");

    setPixmap(QPixmap(Waluigi_Animation[1]));

    QTimer *beat = new QTimer;
    connect(beat,SIGNAL(timeout()),this,SLOT(timing()));

    connect(reloading,SIGNAL(timeout()),this,SLOT(timbullet()));

    QTimer *End_of_Safety = new QTimer;
    connect(End_of_Safety,SIGNAL(timeout()),this,SLOT(Ending()));

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(1000);

    beat->start(2);
    reloading->start(5000);
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

    if (key == Qt::Key_Space && WarioCorp_Stache_Wax == true)
    {
        if(reload == true)
        {
            Bullet *bullet = new Bullet();
            bullet->setPos(positionX, positionY+100);
            scene()->addItem(bullet);
            reload = false;
            reloading->setInterval(5000);
        }
    }
}

void Waluigi::keyReleaseEvent(QKeyEvent *e)
{
    int key = e->key();

    if (key == Qt::Key_Left) {e->accept(); imput[0] = false;}
    if (key == Qt::Key_Right) {e->accept(); imput[1] = false;}
}

void Waluigi::turn_Left(int numbered_Animation)
{
    if (numbered_Animation == 0) {setPixmap(QPixmap(Waluigi_Animation[1])); compteur_Animation = 1;}
    if (numbered_Animation == 1) {setPixmap(QPixmap(Waluigi_Animation[2])); compteur_Animation = 2;}
    if (numbered_Animation == 2) {setPixmap(QPixmap(Waluigi_Animation[3])); compteur_Animation = 3;}
    if (numbered_Animation == 3) {setPixmap(QPixmap(Waluigi_Animation[4])); compteur_Animation = 4;}
    if (numbered_Animation == 4) {setPixmap(QPixmap(Waluigi_Animation[5])); compteur_Animation = 5;}
    if (numbered_Animation == 5) {setPixmap(QPixmap(Waluigi_Animation[6])); compteur_Animation = 6;}
    if(velocityY < 0) {setPixmap(QPixmap(Waluigi_Animation[7])); compteur_Animation = 7;}
}

void Waluigi::turn_Right(int numbered_Animation)
{
    if (numbered_Animation == 0) {setPixmap(QPixmap(Waluigi_Animation[8])); compteur_Animation = -1;}
    if (numbered_Animation == 1) {setPixmap(QPixmap(Waluigi_Animation[9])); compteur_Animation = -2;}
    if (numbered_Animation == 2) {setPixmap(QPixmap(Waluigi_Animation[10])); compteur_Animation = -3;}
    if (numbered_Animation == 3) {setPixmap(QPixmap(Waluigi_Animation[11])); compteur_Animation = -4;}
    if (numbered_Animation == 4) {setPixmap(QPixmap(Waluigi_Animation[12])); compteur_Animation = -5;}
    if (numbered_Animation == 5) {setPixmap(QPixmap(Waluigi_Animation[13])); compteur_Animation = -6;}
    if(velocityY < 0) {setPixmap(QPixmap(Waluigi_Animation[14])); compteur_Animation = -7;}
}

void Waluigi::Animation(bool isWall)
{
    if(isWall == false)
    {
        if (imput[0] == true && imput[1] == false) { turn_Left(timing_Animation/30); }
        if (imput[1] == true && imput[0] == false) { turn_Right(timing_Animation/30); }
        if (imput[0] == false && imput[1] == false || imput[0] == true && imput[1] == true)
        {
            if(compteur_Animation > 0) {setPixmap(QPixmap(Waluigi_Animation[1])); compteur_Animation = 1;
                                        if(velocityY < 0) {setPixmap(QPixmap(Waluigi_Animation[7])); compteur_Animation = 7;}}
            if(compteur_Animation < 0) {setPixmap(QPixmap(Waluigi_Animation[8])); compteur_Animation = -1;
                                        if(velocityY < 0) {setPixmap(QPixmap(Waluigi_Animation[14])); compteur_Animation = -7;}}
        }
    }

    if(isWall == true)
    {
        if(positionX < 40) {setPixmap(QPixmap(Waluigi_Animation[15])); compteur_Animation = 8;}
        if(positionX > 1500) {setPixmap(QPixmap(Waluigi_Animation[16])); compteur_Animation = -8;}
    }
}

bool Waluigi::Contact(float Waluigi_Position_Y, float Source_Contact)
{
    if(Waluigi_Position_Y - Source_Contact <= 10.f && Waluigi_Position_Y - Source_Contact >= -10.f) return true;
    else return false;
}

void Waluigi::timing()
{
    if(timing_Animation < 150) timing_Animation++;
    else timing_Animation = 1;

    if (imput[0] == true) { if(abs(velocityX) < cap_velocityX) velocityX -= 0.1f;}
    if (imput[1] == true) { if(abs(velocityX) < cap_velocityX) velocityX += 0.1f;}

    if(velocityX > 0) velocityX -= 0.03f;
    if(velocityX < 0) velocityX += 0.03f;

    if(velocityX > 0 && velocityX < 0.03) velocityX = 0;
    if(velocityX < 0 && velocityX > -0.03) velocityX = 0;

    QList<QGraphicsItem *> colliding_items = collidingItems();
    int grounded = 900;
    int grip_Wall = -1;
    bool heigh = false;

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid(*(colliding_items[i])) == typeid(Platform) || typeid(*(colliding_items[i])) == typeid(Bullet) || typeid(*(colliding_items[i])) == typeid(Wall))
        {
            bool ContactFoot = Contact(positionY+100, colliding_items[i]->y());
            bool ContactHead = Contact(positionY, colliding_items[i]->y());

            if(typeid(*(colliding_items[i])) == typeid(Wall))
            {
                if (positionX < 40 && compteur_Animation > 0) grip_Wall = colliding_items[i]->x()+20;
                if (positionX > 1500 && compteur_Animation < 0) grip_Wall = colliding_items[i]->x()-73;
            }

            else if(ContactFoot == true && velocityY >= 0.2f)
            {
                grounded = colliding_items[i]->y()-100;
                heigh = true;
            }

            else if(ContactHead == true && velocityY <= -0.1f && Gharlic == false)
            {
                velocityY = 0;
            }

            else if(ContactHead == false && ContactFoot == false && Gharlic == false)
            {
                velocityX = 0;
            }
        }

        if(typeid(*(colliding_items[i])) == typeid(Powerup))
        {
            if(Yoshi_Slippers == false) Yoshi_Slippers = true;
            else if(Gharlic == false) Gharlic = true;
            else if(WarioCorp_Stache_Wax == false) WarioCorp_Stache_Wax = true;
            else if(WAHll_Gloves == false) WAHll_Gloves = true;
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
    }

    if (timing_Animation % 30 == 0 && grip_Wall == -1)
    {
        Animation(false);
    }

    if(grip_Wall != -1)
    {
        velocityX = 0.0;

        /*if(WAHll_Gloves == true)
        {*/
            Animation(true);
            velocityY = 0.1;
            firstjump = true;
            doublejump = true;
            positionX = grip_Wall;
        //}
    }

    if(heigh == true)
        {
            positionY = grounded;
            velocityY = 0.0;
            firstjump = true;
            doublejump = true;
        }

    if(heigh == false && Safety_Protocol == true && positionY > 900.3)
    {
         positionY = 900;
         velocityY = 0.0;
         firstjump = true;
         doublejump = true;
    }

    positionX += velocityX;   // Apply horizontal velocity to X position
    positionY += velocityY;   // Apply vertical velocity to X position
    if(velocityY < cap_velocityY && grip_Wall == -1) velocityY += gravity;     // Apply gravity to vertical velocity

    setPos(positionX,positionY);
}

void Waluigi::timbullet()
{
    reload = true;
}

void Waluigi::Ending()
{
    //Safety_Protocol = false;
}

void Waluigi::spawn()
{
    if(WarioCorp_Stache_Wax == true)
    {
        timer->setInterval(1000);
        Platform * enemy = new Platform(100, 1000, 0.5, 4);
        scene()->addItem(enemy);
    }
    else if(Gharlic == true)
    {
        timer->setInterval(1200);
        Platform * enemy = new Platform(400, 900, 0.4, 2);
        scene()->addItem(enemy);
    }
    else if(Yoshi_Slippers == true)
    {
        Platform * enemy = new Platform(0, 800, 0.4, 2);
        scene()->addItem(enemy);
    }
    else
    {
        Platform * enemy = new Platform(0, 300, 0.35, 1);
        Platform * enemy2 = new Platform(500, 800, 0.35, 1);
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

    if(Gharlic == true && WarioCorp_Stache_Wax == false)
    {
        Powerup * P = new Powerup(600, 900, 3);
        scene()->addItem(P);
    }

    if(WarioCorp_Stache_Wax == true && WAHll_Gloves == false)
    {
        Powerup * P = new Powerup(0, 1000, 4);
        scene()->addItem(P);
    }
}


