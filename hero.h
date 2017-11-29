#ifndef HERO_H
#define HERO_H


class hero
{
public:
    hero();
    void Up_Power(int power);
    void lose();

private:
    const int numberLives_Start = 5;
    int numberLives;

    float speed;
    int position_y;
    int position_x;

    int powerup;
    // 0 : Forme standard

};

#endif // HERO_H
