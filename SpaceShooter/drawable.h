#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable // інтерфейс для відображення ігрових об'єктів
{
public:
    virtual ~Drawable() = 0;
    virtual void Draw(QPainter *painter) = 0;
};

#endif // DRAWABLE_H
