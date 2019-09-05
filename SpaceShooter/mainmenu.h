#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <memory>
#include "gamewindow.h"
#include <fstream>
#include <iostream>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    std::vector<std::string> ReadRecords(std::string path);

private:
    std::shared_ptr<Ui::MainMenu> ui;
    std::shared_ptr<GameWindow> gameWindow;
    std::vector<QLabel*> labels;

private slots:
    void on_PlayButton_clicked();
    void on_QuitButton_clicked();
    void on_RecordsButton_clicked();
    void on_BackButton_clicked();
};

#endif // MAINMENU_H
