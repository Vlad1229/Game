#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "enemy.h"
#include "enemylaser.h"
#include <memory>

struct Direction
{
    bool forward;
    bool back;
    bool right;
    bool left;
};

class Player : public GameObject
{
private:
    double speed;
    int attackCd;
    int attackTimer;
    bool attacking;
    bool shieldIsActive;
    QPixmap shieldImage;
    int health;
    std::shared_ptr<Direction> direction;
public:
    Player(int x, int y);
    void Move();
    void Attack();
    void StartMovingForward();
    void StopMovingForward();
    void StartMovingBack();
    void StopMovingBack();
    void StartMovingRight();
    void StopMovingRight();
    void StartMovingLeft();
    void StopMovingLeft();
    std::shared_ptr<Direction> GetDirection();
    void Draw(QPainter *painter) override;
    bool isAttacking();
    int GetHealth();
    bool CheckForCollision(Enemy *enemy);
    bool CheckForCollision(EnemyLaser *laser);
    void Damage();
    void RestoreHealth();
    void ActivateShield();
    void DeactivateShield();
    bool ShieldIsActive();
};

#endif // PLAYER_H
