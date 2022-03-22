#pragma once
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QDateTime>
#include <QRandomGenerator>
#include <QTimer>
#include <QKeyEvent>
#include <QFont>
#include <QFontDatabase>
#include <QFile>

#include <iostream>
#include <algorithm>
#include <iterator>

#include <enemy.h>
#include <bullet.h>
#include <defender.h>

using namespace std;

class Game : public QWidget
{
    Q_OBJECT

    static const int SC_WIDTH = 1024;
    static const int SC_HEIGHT = 768;
    static const int LAST_LINE = 696;
    QList<Enemy> enemy_list;
    QList<Bullet> bullet_list;
    QList<Bullet> enemy_bullet;
    QList<QString> play_list;
    QRandomGenerator *gen;
    Defender *def;
    QTimer *timer;
    QPoint *blast;
    int timerId;
    int army_size = 0;
    int left_flank = SC_WIDTH;
    int right_flank = 0;
    int enemy_line = 0;
    bool m_e_r = true;
    bool m_e_l = false;
    bool the_end = false;
    bool winner = false;

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void paintEvent(QPaintEvent *e) override;
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void intersecting();
    void enemyMoving();
    void shoot();
    void game_over(QPainter *p);
    void you_win(QPainter *p);

    bool getThe_end() const;
    void setThe_end(bool end);
    int getArmy_size() const;
    void setArmy_size(int as);
    int getLeft_flank() const;
    void setLeft_flank(int lf);
    int getRight_flank() const;
    void setRight_flank(int rf);
    bool e_r() const;
    void setE_r(bool mr);
    bool e_l() const;
    void setE_l(bool ml);
    int getEnemy_line() const;
    void setEnemy_line(int el);
    bool getWinner() const;
    void setWinner(bool w);
    QPoint *getBlast() const;
    void setBlast(QPoint *bl);
};
