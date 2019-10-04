#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "enemy.h"

class SpaceShip : public Enemy, public BlockAlloc<SpaceShip, 3>
{
private:
    int attackCd;
    int attackTimer;
    int attacking;
public:
    SpaceShip(int x, int y);
    void Move() override;
    void Draw(QPainter *painter) override;
    void Attack();
    bool isAttacking();
};

#endif // SPACESHIP_H
