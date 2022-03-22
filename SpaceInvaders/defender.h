#pragma once
#include "unit.h"

class Defender : public Unit
{
public:
    Defender();
    Defender(int x, int y);
    Defender(int x, int y, const QString &s);
    ~Defender();

    const QRect &getRect() const;
    void setRect(const QRect &r);
    const QImage &getImage() const;
    void setImage(const QImage &i);
};
