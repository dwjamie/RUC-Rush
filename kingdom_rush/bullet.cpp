#include "bullet.h"

extern Game *game;

Bullet::Bullet(int level) :
    level(level)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Bullet::move() {
    if (target) {
        QLineF path(pos(), target->pos() + QPointF(15,15));

        if (path.length() < 10) {
            hitTarget();
            return;
        }

        double angle = -1 * path.angle();

        setRotation(angle);

        double dy = speed * qSin(qDegreesToRadians(angle));
        double dx = speed * qCos(qDegreesToRadians(angle));

        setPos(x() + dx, y() + dy);
    } else {
        game->removeItem(this);
    }
}

void Bullet::hitTarget() {
    if (target->died == false) {
        playEnemyHitSound();
        target->getsHurt(damage);
    }

    game->removeItem(this);
}

Arrow::Arrow(int level) : Bullet(level) {
    setPixmap(QPixmap(":/Resource/Bullet/Arrow/Arrow.png"));
    QSound::play(":/Resource/Bullet/Arrow/Release.wav");

    if (level == 1) {
        speed = 6;
        damage = 4;
    } else {
        speed = 6;
        damage = 6;
    }
}

void Arrow::playEnemyHitSound() {
    QSound::play(":/Resource/Bullet/Arrow/Hit.wav");
}

Fireball::Fireball(int level) : Bullet(level) {
    //QSound::play(":/Resource/Bullet/Fireball/Unleash.wav");

    if (level == 1) {
        setPixmap(QPixmap(":/Resource/Bullet/Fireball/Bomb.png"));
        speed = 3;
        damage = 10;
    } else {
        setPixmap(QPixmap(":/Resource/Bullet/Fireball/Missile.png"));
        speed = 3;
        damage = 15;
    }
}

void Fireball::playEnemyHitSound() {
    QSound::play(":/Resource/Bullet/Fireball/Hit.wav");
}

Spell::Spell(int level) : Bullet(level) {
    QSound::play(":/Resource/Bullet/Spell/Shot.wav");

    if (level == 1) {
        setPixmap(QPixmap(":/Resource/Bullet/Spell/Spell_1.png"));
        speed = 2.5;
        damage = 15;
    } else {
        setPixmap(QPixmap(":/Resource/Bullet/Spell/Spell_2.png"));
        speed = 2.5;
        damage = 25;
    }
}

void Spell::playEnemyHitSound() {
    QSound::play(":/Resource/Bullet/Spell/Hit.wav");
}
