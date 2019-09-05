#include "spaceship.h"

SpaceShip::SpaceShip(int x, int y) : Enemy(x, y, 40, 40)
{
    pix = QPixmap(":/resource/png/enemyShip.png");
    attackCd = 1500;
    attackTimer = 600;
    attacking = false;
    speed = 0.2;
}

void SpaceShip::Move()
{
    exactY += speed;
    y = static_cast<int>(floor(exactY));
    Attack();
}

void SpaceShip::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
}

void SpaceShip::Attack()
{
    attacking = attackTimer <= 0;
    if (attacking)
    {
        attackTimer = attackCd;
    }
    attackTimer -= 1;
}

bool SpaceShip::isAttacking()
{
    return attacking;
}
