#ifndef SMALLMETEOR_H
#define SMALLMETEOR_H

#include "enemy.h"
#include "blockalloc.h"

class SmallMeteor : public Enemy, public BlockAlloc<SmallMeteor, 11>
{
public:
    SmallMeteor(int x, int y);
    void Move() override;
    void Draw(QPainter *painter) override;
};

#endif // SMALLMETEOR_H
