#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable
{
public:
    virtual ~Drawable() = 0;
    virtual void Draw(QPainter *painter) = 0;
};

#endif // DRAWABLE_H
