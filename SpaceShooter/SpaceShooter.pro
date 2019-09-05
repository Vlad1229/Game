######################################################################
# Automatically generated by qmake (3.1) Thu Sep 5 18:00:19 2019
######################################################################

QT += core gui
QT += widgets
TEMPLATE = app
TARGET = SpaceShooter
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += bigmeteor.h \
           blockalloc.h \
           drawable.h \
           enemy.h \
           enemylaser.h \
           game.h \
           gameobject.h \
           gamewindow.h \
           laser.h \
           mainmenu.h \
           memorypool.h \
           player.h \
           playerlaser.h \
           smallmeteor.h \
           spaceship.h \
           ufo.h \
           ui_gamewindow.h \
           ui_mainmenu.h
FORMS += gamewindow.ui mainmenu.ui
SOURCES += bigmeteor.cpp \
           drawable.cpp \
           enemy.cpp \
           enemylaser.cpp \
           game.cpp \
           gameobject.cpp \
           gamewindow.cpp \
           laser.cpp \
           main.cpp \
           mainmenu.cpp \
           player.cpp \
           playerlaser.cpp \
           smallmeteor.cpp \
           spaceship.cpp \
           ufo.cpp
RESOURCES += resource.qrc