#include "game.h"

Game::Game(int width, int height)
{
    player = std::shared_ptr<Player>(new Player(180, 560));
    this->width = width;
    this->height = height;
    timer = 1;
    paused = false;
    defeat = false;
    score = 0;
    for (int i = 0; i < 3; i++)
    {
        std::shared_ptr<Background> background(new Background());
        background->x = 0;
        background->y = i * 399;
        background->image = QPixmap(":/resource/png/Background/starBackground.png");
        backgrounds.push_back(background);
    }
}

void Game::Play()
{
    if (!paused)
    {
        timer += 1;

        player->Move();
        if (player->isAttacking())
        {
            std::shared_ptr<PlayerLaser> laser(new PlayerLaser(player->GetX() + player->GetWidth()/2 - 3, player->GetY() - 22));
            playerLasers.push_back(laser);
        }


        for (std::shared_ptr<PlayerLaser> laser : playerLasers)
        {
            laser->Move();

        }

        for (std::shared_ptr<EnemyLaser> laser : enemyLasers)
        {
            laser->Move();
        }

        for (std::shared_ptr<Enemy> enemy : enemies)
        {
            enemy->Move();

            if (dynamic_cast<SpaceShip*>(enemy.get()))
            {
                std::shared_ptr<SpaceShip> ship = std::dynamic_pointer_cast<SpaceShip>(enemy);

                if (ship->isAttacking())
                {
                    std::shared_ptr<EnemyLaser> laser(new EnemyLaser(ship->GetX() + ship->GetWidth()/2 - 3, ship->GetY() + ship->GetHeight()));
                    enemyLasers.push_back(laser);
                }
            }
            else if (dynamic_cast<UFO*>(enemy.get()))
            {
                std::shared_ptr<UFO> ufo = std::dynamic_pointer_cast<UFO>(enemy);

                if (ufo->isAttacking())
                {
                    std::shared_ptr<EnemyLaser> laser(new EnemyLaser(ufo->GetX() + ufo->GetWidth()/2 - 3, ufo->GetY() + ufo->GetHeight()));
                    enemyLasers.push_back(laser);
                }
            }
        }

        CheckForCollision();
        CheckGameObjects();
        CreateEnemies();
        CheckPlayer();
        MoveBackground();
    }
}

void Game::ReactOnPress(QKeyEvent *e)
{
    if (!paused)
    {
        switch (e->key())
        {
        case (Qt::Key_A):
            player->StartMovingLeft();
            break;
        case (Qt::Key_D):
            player->StartMovingRight();
            break;
        case (Qt::Key_S):
            player->StartMovingBack();
            break;
        case (Qt::Key_W):
            player->StartMovingForward();
            break;
        case (Qt::Key_Space):
            player->Attack();
            break;
        }
    }

    if (!defeat && e->key() == Qt::Key_Escape)
    {
        paused = !paused;
    }
}

void Game::ReactOnRelease(QKeyEvent *e)
{
    if (e->key() == Qt::Key_A && !e->isAutoRepeat())
    {
        player->StopMovingLeft();
    }

    if (e->key() == Qt::Key_D && !e->isAutoRepeat())
    {
        player->StopMovingRight();
    }

    if (e->key() == Qt::Key_S && !e->isAutoRepeat())
    {
        player->StopMovingBack();
    }

    if (e->key() == Qt::Key_W && !e->isAutoRepeat())
    {
        player->StopMovingForward();
    }
}

void Game::DrawGame(QPainter *painter)
{
    for (std::shared_ptr<Background> background : backgrounds)
    {
        painter->drawPixmap(static_cast<int>(floor(background->x)), static_cast<int>(floor(background->y)), 400, 400, background->image);
    }

    player->Draw(painter);
    for (std::shared_ptr<PlayerLaser> laser : playerLasers)
    {
        laser->Draw(painter);
    }

    for (std::shared_ptr<EnemyLaser> laser : enemyLasers)
    {
        laser->Draw(painter);
    }

    for (std::shared_ptr<Enemy> enemy : enemies)
    {
        enemy->Draw(painter);
    }
}

void Game::CheckGameObjects()
{
    if (playerLasers.size() > 0 && playerLasers[0]->GetY() < 0)
    {
        playerLasers.erase(playerLasers.begin());
    }

    if (enemyLasers.size() > 0 && enemyLasers[0]->GetY() > height)
    {
        enemyLasers.erase(enemyLasers.begin());
    }

    if (enemies.size() > 0 && (enemies[0]->GetY() > height || enemies[0]->GetX() < 0))
    {
        enemies.erase(enemies.begin());
    }
}

void Game::CheckForCollision()
{
    if (player->GetX() < 0)
    {
        player->SetX(0);
    }
    else if (player->GetX() > width - player->GetWidth())
    {
        player->SetX(width - player->GetWidth());
    }
    else if (player->GetY() < 0)
    {
        player->SetY(0);
    }
    else if (player->GetY() > height - player->GetWidth())
    {
        player->SetY(height - player->GetWidth());
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        {
            for (size_t j = 0; j < playerLasers.size(); j++)
            {
                if (enemies[i]->CheckForCollision(playerLasers[j].get()))
                {
                    if (dynamic_cast<SpaceShip*>(enemies[i].get()))
                    {
                        score += 10;
                    }
                    else if (dynamic_cast<BigMeteor*>(enemies[i].get()))
                    {
                        std::shared_ptr<SmallMeteor> meteor1(new SmallMeteor(enemies[i]->GetX(), enemies[i]->GetY()));
                        enemies.push_back(meteor1);

                        std::shared_ptr<SmallMeteor> meteor2(new SmallMeteor(enemies[i]->GetX() + 20, enemies[i]->GetY()));
                        enemies.push_back(meteor2);
                    }
                    else if (dynamic_cast<UFO*>(enemies[i].get()))
                    {
                        player->ActivateShield();
                        score+= 100;
                    }
                    enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i]));
                    playerLasers.erase(std::find(playerLasers.begin(), playerLasers.end(), playerLasers[i]));
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (player->CheckForCollision(enemies[i].get()))
        {
            enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i]));
            if (player->ShieldIsActive())
            {
                player->DeactivateShield();
            }
            else
            {
                player->Damage();
            }
        }
    }

    for (size_t i = 0; i < enemyLasers.size(); i++)
    {
        if (player->CheckForCollision(enemyLasers[i].get()))
        {
            enemyLasers.erase(std::find(enemyLasers.begin(), enemyLasers.end(), enemyLasers[i]));
            if (player->ShieldIsActive())
            {
                player->DeactivateShield();
            }
            else
            {
                player->Damage();
            }
        }
    }
}

void Game::CreateEnemies()
{
    if (timer % 500 == 0)
    {
        std::shared_ptr<SmallMeteor> meteor(new SmallMeteor(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(meteor);
    }

    if (timer % 2000 == 0)
    {
        std::shared_ptr<BigMeteor> meteor(new BigMeteor(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(meteor);
    }

    if (timer % 1500 == 0)
    {
        std::shared_ptr<SpaceShip> ship(new SpaceShip(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(ship);
    }

    if (timer % 20000 == 0)
    {
        std::shared_ptr<UFO> ufo(new UFO(width, QRandomGenerator::global()->bounded(4) * 10 + 60));
        enemies.push_back(ufo);
    }

    if (timer % 60000 == 0)
    {
        timer = 0;
    }
}

void Game::CheckPlayer()
{
    if (player->GetHealth() <= 0)
    {
        paused = true;
        defeat = true;
        WriteRecord("records.txt");
    }
}

bool Game::isPaused()
{
    return paused;
}

bool Game::isOver()
{
    return defeat;
}

void Game::Resume()
{
    paused = false;
}

void Game::Restart()
{
    score = 0;
    timer = 0;
    player->SetX(180);
    player->SetY(560);
    enemies.clear();
    enemyLasers.clear();
    playerLasers.clear();
    paused = false;
    defeat = false;
    player->RestoreHealth();
    player->DeactivateShield();
}

void Game::MoveBackground()
{
    for (std::shared_ptr<Background> background : backgrounds)
    {
        if (background->y > height)
        {
            background->y -= 1197;
        }
        background->y += 0.1;
    }
}

int Game::GetScore()
{
    return score;
}

int Game::GetPlayerHealth()
{
    return player->GetHealth();
}

void Game::WriteRecord(std::string path)
{
    std::vector<int> records;
    std::string line;

    std::ifstream in(path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            records.push_back(std::stoi(line));
        }
    }
    in.close();

    records.push_back(score);
    sort(records.begin(), records.end());
    records.erase(unique(records.begin(), records.end()), records.end());
    
    std::ofstream out;
    out.open(path);
    if (out.is_open())
    {
        size_t count = 0;
        if (records.size() > 5)
        {
            count = 5;
        }
        else
        {
            count = records.size();
        }

        for (size_t i = 0; i < count; i++)
        {
            out << records[records.size() - (i + 1)] << std::endl;
        }
    }
}
