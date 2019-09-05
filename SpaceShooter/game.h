#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <QKeyEvent>
#include <memory>
#include <QRandomGenerator>
#include <fstream>
#include "smallmeteor.h"
#include "bigmeteor.h"
#include "spaceship.h"
#include "ufo.h"
#include "enemylaser.h"
#include "playerlaser.h"

struct Background
{
    double x;
    double y;
    QPixmap image;
};

class Game
{
private:
    int width;
    int height; // ширина і довжина вікна
    int timer;
    int score;
    bool paused;
    bool defeat;
    std::vector<std::shared_ptr<Background>> backgrounds;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<PlayerLaser>> playerLasers;
    std::vector<std::shared_ptr<EnemyLaser>> enemyLasers;
public:
    Game(int width, int height);
    void ReactOnPress(QKeyEvent *e);
    void ReactOnRelease(QKeyEvent *e);
    void DrawGame(QPainter *painter);
    void Play();
    void CheckGameObjects();
    void CheckForCollision();
    void CreateEnemies();
    void CheckPlayer();
    void MoveBackground();
    bool isPaused();
    bool isOver();
    void Resume();
    void Restart();
    int GetScore();
    int GetPlayerHealth();
    void WriteRecord(std::string path);
};

#endif // GAME_H
