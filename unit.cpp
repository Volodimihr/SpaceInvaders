#include "unit.h"

const QRect &Unit::getRect() const
{
    return rect;
}

const QImage &Unit::getImage() const
{
    return image;
}

void Unit::setRect(const QRect &r)
{
    rect = r;
}

void Unit::setImage(const QImage &i)
{
    image = i;
}

void Unit::load(const QString &s)
{
    image.load(s);
    rect = image.rect();
}

void Unit::translate(int ax, int ay)
{
    rect.translate(ax, ay);
}

Unit::Unit():QImage(), QRect(){};

bool Unit::getDead() const
{
    return dead;
}

void Unit::setDead(const bool &d)
{
    dead = d;
}

Unit::Unit(int x, int y)
    :QImage(), QRect()
{
    image.load(":/tst2");
    rect = QRect(image.rect());
    rect.translate(x, y);
}

Unit::Unit(int x, int y, const QString &s)
    :QImage(), QRect()
{
    image.load(s);
    rect = QRect(image.rect());
    rect.translate(x, y);
}

Unit::~Unit() = default;
