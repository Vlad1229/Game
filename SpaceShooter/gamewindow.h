#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QTimer>
#include <memory>
#include "game.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

private:
    std::shared_ptr<Ui::GameWindow> ui;
    QTimer *tmr;
    std::unique_ptr<Game> game;

private slots:
    void closeEvent (QCloseEvent *event);
    void paintEvent(QPaintEvent* e);
    void updateTime();
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);
    void on_ResumeButton_clicked();
    void on_RestartButton_clicked();
    void on_MainMenuButton_clicked();

signals:
    void MainMenu();
};

#endif // GAMEWINDOW_H
