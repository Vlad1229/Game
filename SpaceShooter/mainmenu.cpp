#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    gameWindow = std::unique_ptr<GameWindow>(new GameWindow());
    connect(gameWindow.get(), &GameWindow::MainMenu, this, &MainMenu::show);

    labels.push_back(ui->Record1);
    labels.push_back(ui->Record2);
    labels.push_back(ui->Record3);
    labels.push_back(ui->Record4);
    labels.push_back(ui->Record5);
    for (size_t i = 0; i < labels.size(); i++)
    {
        labels[i]->setVisible(false);
        labels[i]->setText(QString::number(i + 1) + ". 0");
    }
    ui->BackButton->setVisible(false);
}

void MainMenu::on_PlayButton_clicked()
{
    gameWindow->show();
    this->close();
}

void MainMenu::on_QuitButton_clicked()
{
    qApp->exit();
}

void MainMenu::on_RecordsButton_clicked()
{
    std::vector<std::string> records = ReadRecords("records.txt");
    ui->PlayButton->setVisible(false);
    ui->PlayButton->setEnabled(false);
    ui->RecordsButton->setVisible(false);
    ui->RecordsButton->setEnabled(false);
    ui->QuitButton->setVisible(false);
    ui->QuitButton->setEnabled(false);
    for (QLabel* label : labels)
    {
        label->setVisible(true);
    }
    ui->BackButton->setVisible(true);
    ui->BackButton->setEnabled(true);
    for (size_t i = 0; i < records.size(); i++)
    {
        labels[i]->setText(QString::number(i + 1) + ". " + QString::fromStdString(records[i]));
    }
    for (size_t i = records.size(); i < 5; i++)
    {
        labels[i]->setText(QString::number(i + 1) + ". 0");
    }
}

void MainMenu::on_BackButton_clicked()
{
    ui->PlayButton->setVisible(true);
    ui->PlayButton->setEnabled(true);
    ui->RecordsButton->setVisible(true);
    ui->RecordsButton->setEnabled(true);
    ui->QuitButton->setVisible(true);
    ui->QuitButton->setEnabled(true);
    for (QLabel* label : labels)
    {
        label->setVisible(false);
    }
    ui->BackButton->setVisible(false);
    ui->BackButton->setEnabled(false);
}

std::vector<std::string> MainMenu::ReadRecords(std::string path)
{
    std::vector<std::string> records;
    std::string line;

    std::ifstream in(path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            records.push_back(line);
        }
    }
    in.close();
    return records;
}
