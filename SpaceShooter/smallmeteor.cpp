#include "smallmeteor.h"

SmallMeteor::SmallMeteor(int x, int y) : Enemy(x, y, 20, 20)
{
    pix = QPixmap(":/resource/png/meteorSmall.png");
    speed = 0.3;
}

void SmallMeteor::Move()
{
    exactY += speed;
    y = static_cast<int>(floor(exactY));
}

void SmallMeteor::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
}
