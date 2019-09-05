#include "gameobject.h"

GameObject::GameObject(int x, int y, int width, int height)
{
    exactX = this->x = x;
    exactY = this->y = y;
    this->width = width;
    this->height = height;
}

int GameObject::GetX()
{
    return x;
}

int GameObject::GetY()
{
    return y;
}

int GameObject::GetWidth()
{
    return width;
}

int GameObject::GetHeight()
{
    return height;
}

void GameObject::SetX(int x)
{
    exactX = this->x = x;
}

void GameObject::SetY(int y)
{
    exactY = this->y = y;
}

void GameObject::SetWidth(int width)
{
    this->width = width;
}

void GameObject::SetHeight(int height)
{
    this->height = height;
}
