#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "enemy.h"

class SpaceShip : public Enemy, public BlockAlloc<SpaceShip, 3>
{
private:
    int attackCd; // інтервал між пострілами
    int attackTimer; // час до нового пострілу
    int attacking; // логічне значення, що показує, чи атакує ворог
public:
    SpaceShip(int x, int y);
    void Move() override;
    void Draw(QPainter *painter) override;
    void Attack();
    bool isAttacking();
};

#endif // SPACESHIP_H
