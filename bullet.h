#pragma once
#include "unit.h"

class Bullet : public Unit
{
public:
    Bullet();
    Bullet(int x, int y, const QString &s);
    ~Bullet();

    const QRect &getRect() const;
    void setRect(const QRect &r);
};
