#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include "laser.h"

class PlayerLaser : public Laser
{
public:
    PlayerLaser(int x, int y);
    void Draw(QPainter *painter) override;
};

#endif // PLAYERLASER_H
