#include "player.h"
#include "memorypool.h"

Player::Player(int x, int y) : GameObject (x, y, 40, 40)
{
    pix = QPixmap(":/resource/png/player.png");
    shieldImage = QPixmap(":/resource/png/shield.png");
    shieldIsActive = false;
    speed = 0.3;
    direction = std::shared_ptr<Direction>(new Direction());
    direction->forward = direction->back = direction->right = direction->left = false;
    attackCd = 200;
    attackTimer = 0;
    attacking = false;
    health = 4;
}

void Player::StartMovingForward(){
    direction->forward = true;
}

void Player::StopMovingForward(){
    direction->forward = false;
}

void Player::StartMovingBack(){
    direction->back = true;
}

void Player::StopMovingBack(){
    direction->back = false;
}

void Player::StartMovingRight(){
    direction->right = true;
}

void Player::StopMovingRight(){
    direction->right = false;
}

void Player::StartMovingLeft(){
    direction->left = true;
}

void Player::StopMovingLeft(){
    direction->left = false;
}

void Player::Move()
{
    exactX += (direction->right - direction->left) * speed;
    exactY += (direction->back - direction->forward) * speed;
    x = static_cast<int>(floor(exactX));
    y = static_cast<int>(floor(exactY));
    attackTimer -= 1;
    attacking = attackTimer >= 199;
}

std::shared_ptr<Direction> Player::GetDirection()
{
    return direction;
}

void Player::Draw(QPainter *painter)
{
    painter->drawPixmap(x, y, width, height, pix);
    if (shieldIsActive)
    {
        painter->drawPixmap(x - static_cast<int>(width * 0.25), y  - static_cast<int>(height * 0.25), static_cast<int>(width * 1.5), static_cast<int>(height * 1.5), shieldImage);
    }
}

void Player::Attack()
{
    attacking = (attackTimer <= 0);
    if (attacking)
    {
        attackTimer = attackCd;
    }
}

bool Player::isAttacking()
{
    return attacking;
}

int Player::GetHealth()
{
    return health;
}

bool Player::CheckForCollision(EnemyLaser *laser)
{
    return ((laser->GetX() + laser->GetWidth() > x && laser->GetX() < x + width)
           && (laser->GetY() + laser->GetHeight() > y) && laser->GetY() < y + height);
}

bool Player::CheckForCollision(Enemy *enemy)
{
    return ((enemy->GetX() + enemy->GetWidth() > x && enemy->GetX() < x + width)
           && (enemy->GetY() + enemy->GetHeight() > y) && enemy->GetY() < y + height);
}

void Player::Damage()
{
    health -= 1;
}

void Player::RestoreHealth()
{
    health = 3;
}

void Player::ActivateShield()
{
    shieldIsActive = true;
}

void Player::DeactivateShield()
{
    shieldIsActive = false;
}

bool Player::ShieldIsActive()
{
    return shieldIsActive;
}
