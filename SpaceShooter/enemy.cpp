#include "enemy.h"

Enemy::Enemy(int x, int y, int width, int height) : GameObject (x, y, width, height)
{

}

bool Enemy::CheckForCollision(PlayerLaser *laser)
{
    return ((laser->GetX() + laser->GetWidth() > x && laser->GetX() < x + width)
           && (laser->GetY() + laser->GetHeight() > y) && laser->GetY() < y + height); /* перевірка чи перетинається цей ворог
                                                                                          з лазером гравця */
}
