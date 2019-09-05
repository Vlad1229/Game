#include "laser.h"

Laser::Laser(int x, int y) : GameObject (x, y, 6, 22)
{

}

void Laser::Move()
{
    exactY += speed;
    y = static_cast<int>(floor(exactY));
}
