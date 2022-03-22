#include "defender.h"

Defender::Defender():Unit(){}

Defender::Defender(int x, int y):Unit(x, y){}

Defender::Defender(int x, int y, const QString &s):Unit(x, y, s){}

Defender::~Defender(){}

const QRect &Defender::getRect() const
{
    return rect;
}

void Defender::setRect(const QRect &r)
{
    rect = r;
}

const QImage &Defender::getImage() const
{
    return image;
}

void Defender::setImage(const QImage &i)
{
    image = i;
}
