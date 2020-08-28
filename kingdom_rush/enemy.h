#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"
#include <qmath.h>
#include <QTimer>
#include <QSound>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Enemy();
    int getSpawnedOrder() const;
    void getsHurt(int damage);
    virtual void dies() = 0;
    virtual void setWayPoint(QList<QPointF> Wpoints);

    friend class Tower;
    friend class Bullet;
    friend class Game;

public slots:
    virtual void march() = 0;
    void getsRemoved();

protected:
    QList<QPointF> way_points;
    QPointF next_point;
    QTimer *march_timer;
    int point_index;
    double speed;            //移速
    int hp;                  //生命值
    int bounty;              //击杀赏金
    int damage;              //对基地造成的生命值损失点数
    int spawned_order;       //是第几个被创造的敌人
    bool died;
    static int static_spawn_order;
};

class Goblin : public Enemy {
    Q_OBJECT

public:
    Goblin(QList<QPointF> way_points);
    void dies();

public slots:
    void march();
};

class Juggernaut : public Enemy {
    Q_OBJECT

public:
    Juggernaut(QList<QPointF> way_points);
    void setWayPoint(QList<QPointF> way_points);
    void dies();

public slots:
    void march();
};

class Orc : public Enemy {
    Q_OBJECT

public:
    Orc(QList<QPointF> way_points);
    void dies();

public slots:
    void march();
};

class Troll : public Enemy {
    Q_OBJECT

public:
    Troll(QList<QPointF> way_points);
    void dies();

public slots:
    void march();
};

#endif // ENEMY_H

