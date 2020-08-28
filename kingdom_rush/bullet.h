#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"
#include <qmath.h>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Bullet(int level);
    void hitTarget();
    virtual void playEnemyHitSound() = 0;

signals:

public slots:
    void move();

protected:
    Enemy *target;
    int level;
    double speed;
    int damage;
};

class Arrow : public Bullet {
public:
    Arrow(int level);
    void playEnemyHitSound();

    friend class Archer;
};

class Fireball : public Bullet {
public:
    Fireball(int level);
    void playEnemyHitSound();

    friend class Artillery;
};

class Spell : public Bullet {
public:
    Spell(int level);
    void playEnemyHitSound();

    friend class Mage;
};


#endif // BULLET_H
