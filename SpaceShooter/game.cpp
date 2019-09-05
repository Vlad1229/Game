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

void Game::Play() // функція, що викликається кожен інтервал таймера ігрового вікна
{
    if (!paused)
    {
        timer += 1;

        player->Move();
        if (player->isAttacking()) // якщо гравець атакує, створює лазер і додає до вектору
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

        for (std::shared_ptr<Enemy> enemy : enemies) // проходиться по всім ворогам
        {
            enemy->Move();

            if (dynamic_cast<SpaceShip*>(enemy.get())) /* якщо це космічний корабель або літаюча тарілка,
                                                          і цей ворог атакує, то створює ворожий лазер */
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

void Game::ReactOnPress(QKeyEvent *e) // функція для обробки натискання клавіш
{
    if (!paused) // виконується, якщо гра не на паузі
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

void Game::ReactOnRelease(QKeyEvent *e) // виконується при відпусканні клавіші
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

void Game::DrawGame(QPainter *painter) // малює всі ігрові об'єкти
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

void Game::CheckGameObjects() // видаляє ігрові об'єкти, що виходять за межі вікна
{
    /* оскільки всі лазери і вороги виходять за межі карти в такому ж порядку
       як і створюються, тому перевіряються тільки перші елементи в масивах*/

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
    if (player->GetX() < 0) // перевіряє, чи виходить гравець за межі вікна, і повертає його назад в разі необхідності
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

    for (size_t i = 0; i < enemies.size(); i++) // перевіряє чи перетинаються вороги з лазерами, і видаляє іх у разі перетинання
    {
        {
            for (size_t j = 0; j < playerLasers.size(); j++)
            {
                if (enemies[i]->CheckForCollision(playerLasers[j].get()))
                {
                    if (dynamic_cast<SpaceShip*>(enemies[i].get())) // якщо це космічний корабель додає 10 балів
                    {
                        score += 10;
                    }
                    else if (dynamic_cast<BigMeteor*>(enemies[i].get())) // якщо це великий метеорит, то він розбивається на два малих
                    {
                        std::shared_ptr<SmallMeteor> meteor1(new SmallMeteor(enemies[i]->GetX(), enemies[i]->GetY()));
                        enemies.push_back(meteor1);

                        std::shared_ptr<SmallMeteor> meteor2(new SmallMeteor(enemies[i]->GetX() + 20, enemies[i]->GetY()));
                        enemies.push_back(meteor2);
                    }
                    else if (dynamic_cast<UFO*>(enemies[i].get())) // якщо це літаюча тарілка, то додається 100 балів і активовується щит
                    {
                        player->ActivateShield();
                        score+= 100;
                    }
                    enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i])); // видаляється ворог з масиву ворогів
                    playerLasers.erase(std::find(playerLasers.begin(), playerLasers.end(), playerLasers[i])); // видаляється лазер з масиву лазерів
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (player->CheckForCollision(enemies[i].get())) // перевіряє чи перетинається гравець з ворогом
        {
            enemies.erase(std::find(enemies.begin(), enemies.end(), enemies[i])); //видаляє ворога з масиву
            if (player->ShieldIsActive()) // якщо щит активований, то знищує його, якщо ні, то віднімається здоров'є
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
        if (player->CheckForCollision(enemyLasers[i].get())) // перевіряє чи перетинається гравець з лазером
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
    if (timer % 500 == 0) // кожні 500 інтервалів таймера створюється метеор в випадковому місці по х
    {
        std::shared_ptr<SmallMeteor> meteor(new SmallMeteor(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(meteor);
    }

    if (timer % 2000 == 0) // кожні 2000 інтервалів таймера створюється великий метеор  в випадковому місці по х
    {
        std::shared_ptr<BigMeteor> meteor(new BigMeteor(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(meteor);
    }

    if (timer % 1500 == 0) // кожні 1500 інтервалів таймера створюється космічний корабель  в випадковому місці по х
    {
        std::shared_ptr<SpaceShip> ship(new SpaceShip(QRandomGenerator::global()->bounded(9) * 40, -40));
        enemies.push_back(ship);
    }

    if (timer % 20000 == 0) // кожні 200000 інтервалів таймера створюється літаюча тарілка в випадковому місці від 60 до 100
    {
        std::shared_ptr<UFO> ufo(new UFO(width, QRandomGenerator::global()->bounded(4) * 10 + 60));
        enemies.push_back(ufo);
    }

    if (timer % 60000 == 0) // кожні 60000 інтервалів обнуляється таймер, щоб не йшов до безкінечності
    {
        timer = 0;
    }
}

void Game::CheckPlayer()
{
    if (player->GetHealth() <= 0) // перевіряє здоров'я гравця і завершує гру, якщо воно рівне нулю
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

void Game::Restart() // перезапускає гру, видаляє всіх ворогів і відновлює здоров'я гравця
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

void Game::MoveBackground() // рухає задній фон
{
    for (std::shared_ptr<Background> background : backgrounds)
    {
        if (background->y > height) // якщо фон пройшов вікно, повертається на початок
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

void Game::WriteRecord(std::string path) // записує рекорд в файл
{
    std::vector<int> records;
    std::string line;

    // відкривається файл і рекорди записуються в масив
    std::ifstream in(path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            records.push_back(std::stoi(line));
        }
    }
    in.close();

    // до масиву додається теперешній рахунок, і масив сортується
    records.push_back(score);
    sort(records.begin(), records.end());
    records.erase(unique(records.begin(), records.end()), records.end());

    // відкривається файл і записуються 5 більших результатів з масиву
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
