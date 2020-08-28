#ifndef TOWER_H
#define TOWER_H

#include "bullet.h"
#include <QTimer>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Tower(QPointF pos);
    virtual void upgrade() = 0;
    virtual void attack() = 0;
    bool thisIsEnemy(QGraphicsItem *item) const;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;

    friend class TowerPosition;

signals:

public slots:
    void chooseEnemyToAttack();

protected:
    QGraphicsEllipseItem *attack_area;
    Enemy *target;
    QTimer *attack_rate_timer;
    int level;
    int price;
};

class Archer : public Tower {
public:
    Archer(QPointF pos);
    void upgrade();
    void attack();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class Artillery : public Tower {
public:
    Artillery(QPointF pos);
    void upgrade();
    void attack();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class Mage : public Tower {
public:
    Mage(QPointF pos);
    void upgrade();
    void attack();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOWER_H
