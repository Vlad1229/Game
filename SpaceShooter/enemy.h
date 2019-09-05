#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "playerlaser.h"

class Enemy : public GameObject // абстрактний клас, від якого наслідуються всі вороги
{
protected:
    double speed;
public:
    Enemy(int x, int y, int width, int height);
    virtual void Move() = 0;
    bool CheckForCollision(PlayerLaser *laser);
};

#endif // ENEMY_H
