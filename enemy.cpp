#include "enemy.h"

Enemy::Enemy() = default;

Enemy::Enemy(int x, int y):Unit(x, y){}

Enemy::Enemy(int x, int y, const QString &s):Unit(x, y, s){}

Enemy::~Enemy()
{
}

QRect Enemy::getRect() const
{
    return rect;
}

void Enemy::setRect(const QRect &r)
{
    rect = r;
}
