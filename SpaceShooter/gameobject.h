#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPixmap>
#include "drawable.h"
#include <cmath>

class GameObject : public Drawable
{
protected:
    int x;
    int y;
    double exactX;
    double exactY;
    int width;
    int height;
    QPixmap pix;
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
