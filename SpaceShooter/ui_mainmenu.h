/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QPushButton *PlayButton;
    QPushButton *QuitButton;
    QPushButton *RecordsButton;
    QLabel *Record1;
    QLabel *Record2;
    QLabel *Record3;
    QLabel *Record4;
    QLabel *Record5;
    QPushButton *BackButton;

    void setupUi(QWidget *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainMenu->resize(400, 300);
        PlayButton = new QPushButton(MainMenu);
        PlayButton->setObjectName(QString::fromUtf8("PlayButton"));
        PlayButton->setGeometry(QRect(160, 110, 75, 23));
        QuitButton = new QPushButton(MainMenu);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));
        QuitButton->setGeometry(QRect(160, 170, 75, 23));
        RecordsButton = new QPushButton(MainMenu);
        RecordsButton->setObjectName(QString::fromUtf8("RecordsButton"));
        RecordsButton->setGeometry(QRect(160, 140, 75, 23));
        Record1 = new QLabel(MainMenu);
        Record1->setObjectName(QString::fromUtf8("Record1"));
        Record1->setGeometry(QRect(160, 90, 81, 16));
        Record2 = new QLabel(MainMenu);
        Record2->setObjectName(QString::fromUtf8("Record2"));
        Record2->setGeometry(QRect(160, 110, 81, 16));
        Record3 = new QLabel(MainMenu);
        Record3->setObjectName(QString::fromUtf8("Record3"));
        Record3->setGeometry(QRect(160, 130, 81, 16));
        Record4 = new QLabel(MainMenu);
        Record4->setObjectName(QString::fromUtf8("Record4"));
        Record4->setGeometry(QRect(160, 150, 81, 16));
        Record5 = new QLabel(MainMenu);
        Record5->setObjectName(QString::fromUtf8("Record5"));
        Record5->setGeometry(QRect(160, 170, 81, 16));
        BackButton = new QPushButton(MainMenu);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));
        BackButton->setGeometry(QRect(160, 200, 75, 23));

        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QWidget *MainMenu)
    {
        MainMenu->setWindowTitle(QApplication::translate("MainMenu", "MainMenu", nullptr));
        PlayButton->setText(QApplication::translate("MainMenu", "Play", nullptr));
        QuitButton->setText(QApplication::translate("MainMenu", "Quit", nullptr));
        RecordsButton->setText(QApplication::translate("MainMenu", "Records", nullptr));
        Record1->setText(QString());
        Record2->setText(QString());
        Record3->setText(QString());
        Record4->setText(QString());
        Record5->setText(QString());
        BackButton->setText(QApplication::translate("MainMenu", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
