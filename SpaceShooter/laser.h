#ifndef LASER_H
#define LASER_H

#include "gameobject.h"
#include "blockalloc.h"

class Laser : public GameObject, public BlockAlloc<Laser, 12>
{
protected:
    double speed;
public:
    Laser(int x, int y);
    void Move();
};

#endif // LASER_H
