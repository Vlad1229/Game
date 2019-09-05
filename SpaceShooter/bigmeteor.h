#ifndef BIGMETEOR_H
#define BIGMETEOR_H

#include "enemy.h"
#include "blockalloc.h"

class BigMeteor : public Enemy, public BlockAlloc<BigMeteor, 3>
{
public:
    BigMeteor(int x, int y);
    void Move() override;
    void Draw(QPainter *painter) override;
};

#endif // BIGMETEOR_H
