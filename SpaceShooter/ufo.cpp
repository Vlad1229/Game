#include "ufo.h"

UFO::UFO(int x, int y) : Enemy (x, y, 40, 40)
{
    pix = QPixmap(":/resource/png/enemyUFO.png");
    attackCd = 700;
    attackTimer = 300;
    attacking = false;
    speed = -0.1;
}

void UFO::Move()
{
    exactX += speed;
    x = static_cast<int>(floor(exactX));
    Attack();
}

void UFO::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
}

void UFO::Attack()
{
    attacking = attackTimer <= 0;
    if (attacking)
    {
        attackTimer = attackCd;
    }
    attackTimer -= 1;
}

bool UFO::isAttacking()
{
    return attacking;
}
