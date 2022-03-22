#include "bullet.h"

const QRect &Bullet::getRect() const
{
    return rect;
}

void Bullet::setRect(const QRect &r)
{
    rect = r;
}

Bullet::Bullet():Unit(){}

Bullet::Bullet(int x, int y, const QString &s):Unit(x, y, s){}

Bullet::~Bullet()
{

}
