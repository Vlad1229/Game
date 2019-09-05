#include "playerlaser.h"

PlayerLaser::PlayerLaser(int x, int y) : Laser (x, y)
{
    pix = QPixmap(":/resource/png/laserGreen.png");
    speed = -0.4;
}

void PlayerLaser::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
}
