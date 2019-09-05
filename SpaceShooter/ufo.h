#ifndef UFO_H
#define UFO_H

#include "enemy.h"
#include "blockalloc.h"

class UFO : public Enemy, public BlockAlloc<UFO, 1>
{
private:
    int attackCd;
    int attackTimer;
    int attacking;
public:
    UFO(int x, int y);
    void Move() override;
    void Draw(QPainter *painter) override;
    void Attack();
    bool isAttacking();
};

#endif // UFO_H
