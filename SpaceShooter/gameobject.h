#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPixmap>
#include "drawable.h"
#include <cmath>

class GameObject : public Drawable // базовий клас від якого наслідуються всі ігрові об'єкти
{
protected:
    int x;
    int y;  //координати в цілих числах
    double exactX;
    double exactY;  // точні координати цілих чисел
    int width;
    int height; // довжина і ширина
    QPixmap pix; // малюнок
public:
    GameObject(int x, int y, int width, int height);
    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();
    void SetX(int x);
    void SetY(int y);
    void SetWidth(int width);
    void SetHeight(int height);
};

#endif // GAMEOBJECT_H
