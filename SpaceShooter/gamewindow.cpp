#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->ResumeButton->setVisible(false); // всі клавіші на початку недоступні
    ui->ResumeButton->setEnabled(false);
    ui->RestartButton->setVisible(false);
    ui->RestartButton->setEnabled(false);
    ui->MainMenuButton->setVisible(false);
    ui->MainMenuButton->setEnabled(false);

    tmr = new QTimer(this);
    tmr->setInterval(1); // інтервал таймеру 0,001 секунди
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    game = std::unique_ptr<Game>(new Game(width(), height()));
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint ); // ховається червоний хрестик, що закриває вікно
}

void GameWindow::closeEvent(QCloseEvent *event) // подія при закриванні вікна
{
    game->Restart();
    tmr->stop();
    event->accept();
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    tmr->start();
    QPainter painter(this);
    game->DrawGame(&painter);
    QWidget::paintEvent(e);
}

void GameWindow::updateTime()
{
    game->Play();

    if (game->isOver()) // якщо гра завершена, клавіші "restart" i "main menu" стають доступні
    {
        ui->ResumeButton->setVisible(false);
        ui->ResumeButton->setEnabled(false);
        ui->RestartButton->setVisible(true);
        ui->RestartButton->setEnabled(true);
        ui->MainMenuButton->setVisible(true);
        ui->MainMenuButton->setEnabled(true);
    }
    else if (game->isPaused()) // якщо гра на паузі, клавіші "resume" i "main menu" стають доступні
    {
        ui->ResumeButton->setVisible(true);
        ui->ResumeButton->setEnabled(true);
        ui->RestartButton->setVisible(false);
        ui->RestartButton->setEnabled(false);
        ui->MainMenuButton->setVisible(true);
        ui->MainMenuButton->setEnabled(true);
    }
    else // в іншому випадку всі клавіші недоступні
    {
        ui->ResumeButton->setVisible(false);
        ui->ResumeButton->setEnabled(false);
        ui->RestartButton->setVisible(false);
        ui->RestartButton->setEnabled(false);
        ui->MainMenuButton->setVisible(false);
        ui->MainMenuButton->setEnabled(false);
    }
    ui->ScoreText->setText("Score: " + QString::number(game->GetScore()));
    ui->HealthText->setText("Health " + QString::number(game->GetPlayerHealth()));

    repaint();
}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    game->ReactOnPress(e);
}

void GameWindow::keyReleaseEvent(QKeyEvent *e)
{
    game->ReactOnRelease(e);
}

void GameWindow::on_ResumeButton_clicked()
{
    game->Resume();
}

void GameWindow::on_RestartButton_clicked()
{
    game->Restart();
}

void GameWindow::on_MainMenuButton_clicked()
{
    this->close();
    emit MainMenu();
}
