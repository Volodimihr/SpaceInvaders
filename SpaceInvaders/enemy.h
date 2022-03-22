#pragma once
#include "unit.h"

class Enemy : public Unit
{
public:
    Enemy();
    Enemy(int x, int y);
    Enemy(int x, int y, const QString &s);
    ~Enemy();

    QRect getRect() const;
    void setRect(const QRect &r);
};
