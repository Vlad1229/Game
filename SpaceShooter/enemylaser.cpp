#include "enemylaser.h"

EnemyLaser::EnemyLaser(int x, int y) : Laser (x, y)
{
    pix = QPixmap(":/resource/png/laserRed.png");
    speed = 0.5;
}

void EnemyLaser::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
}
