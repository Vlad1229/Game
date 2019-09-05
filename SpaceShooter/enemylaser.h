#ifndef ENEMYLASER_H
#define ENEMYLASER_H

#include "laser.h"

class EnemyLaser : public Laser
{
public:
    EnemyLaser(int x, int y);
    void Draw(QPainter *painter) override;
};

#endif // ENEMYLASER_H
