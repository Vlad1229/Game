/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QPushButton *ResumeButton;
    QPushButton *MainMenuButton;
    QPushButton *RestartButton;
    QLabel *ScoreText;
    QLabel *HealthText;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(400, 600);
        GameWindow->setMinimumSize(QSize(400, 600));
        GameWindow->setMaximumSize(QSize(400, 600));
        GameWindow->setBaseSize(QSize(400, 600));
        ResumeButton = new QPushButton(GameWindow);
        ResumeButton->setObjectName(QString::fromUtf8("ResumeButton"));
        ResumeButton->setGeometry(QRect(160, 270, 75, 23));
        MainMenuButton = new QPushButton(GameWindow);
        MainMenuButton->setObjectName(QString::fromUtf8("MainMenuButton"));
        MainMenuButton->setGeometry(QRect(160, 300, 75, 23));
        RestartButton = new QPushButton(GameWindow);
        RestartButton->setObjectName(QString::fromUtf8("RestartButton"));
        RestartButton->setGeometry(QRect(160, 270, 75, 23));
        ScoreText = new QLabel(GameWindow);
        ScoreText->setObjectName(QString::fromUtf8("ScoreText"));
        ScoreText->setGeometry(QRect(20, 10, 101, 16));
        HealthText = new QLabel(GameWindow);
        HealthText->setObjectName(QString::fromUtf8("HealthText"));
        HealthText->setGeometry(QRect(20, 30, 101, 16));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "SpaceShooter", nullptr));
        ResumeButton->setText(QApplication::translate("GameWindow", "Resume", nullptr));
        MainMenuButton->setText(QApplication::translate("GameWindow", "Main menu", nullptr));
        RestartButton->setText(QApplication::translate("GameWindow", "Restart", nullptr));
        ScoreText->setText(QApplication::translate("GameWindow", "TextLabel", nullptr));
        HealthText->setText(QApplication::translate("GameWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
