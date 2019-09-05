#include "bigmeteor.h"

BigMeteor::BigMeteor(int x, int y) : Enemy(x, y, 40, 40)
{
    pix = QPixmap(":/resource/png/meteorBig.png");
    speed = 0.15;
}

void BigMeteor::Move()
{
    exactY += speed;
    y = static_cast<int>(floor(exactY)); // до координат додяється переміщення і округлюється
}

void BigMeteor::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix); // відображення об'єкту
}
