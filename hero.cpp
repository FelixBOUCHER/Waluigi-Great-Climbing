#include "hero.h"

hero::hero()
{

}

void hero::Up_Power(int power)
{
    powerup = power;
}

void hero::lose()
{
    numberLives--;
}
