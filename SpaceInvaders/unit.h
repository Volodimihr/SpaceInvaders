#pragma once
#include <QImage>
#include <QRect>

class Unit : public QImage, public QRect
{
protected:
    QRect rect;
    QImage image;
    bool dead = false;
public:
    Unit();
    Unit(int x, int y);
    Unit(int x, int y, const QString &s);
    virtual ~Unit() = 0;

    const QRect &getRect() const;
    const QImage &getImage() const;
    void setRect(const QRect &r);
    void setImage(const QImage &i);
    void load(const QString &s);
    void translate(int ax, int ay); // смещение на определенное количество клеток(пикселей)
    bool getDead() const;
    void setDead(const bool &d);
};
