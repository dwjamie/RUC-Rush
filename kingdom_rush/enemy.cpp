#include "enemy.h"

extern Game *game;

int Enemy::static_spawn_order = 0;

Enemy::Enemy() {
    died = false;

    point_index = 0;

    static_spawn_order++;
    spawned_order = static_spawn_order;

    march_timer = new QTimer(this);
    connect(march_timer, SIGNAL(timeout()), this, SLOT(march()));
    march_timer->start(10);
}

int Enemy::getSpawnedOrder() const {
    return spawned_order;
}

void Enemy::getsHurt(int damage) {
    hp -= damage;

    if (hp <= 0) {
        dies();
        return;
    }
}

void Enemy::setWayPoint(QList<QPointF> way_points_) {
    for(int i = 0; i < way_points_.size(); i++) {
        QPointF adjust(30, 30);
        way_points.append(way_points_[i] - adjust);
    }
}

void Enemy::getsRemoved() {
    game->removeItem(this);
}

Goblin::Goblin(QList<QPointF> way_points) {
    setPixmap(QPixmap(":/Resource/Enemy/Goblin/Left.png"));

    setWayPoint(way_points);
    setPos(way_points[0] - QPointF(20, 20));
    next_point = way_points[1];

    speed = 0.6;
    hp  = 40;
    damage = 1;
    bounty = 10;
}

void Goblin::dies() {
    game->gold += bounty;
    died = true;

    march_timer->stop();

    QLineF path(pos(), next_point);
    if (path.angle() >= 90 && path.angle() < 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Dead_Left.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Dead_Right.png"));
    }

    QSound::play(":/Resource/Enemy/Goblin/Dead.wav");

    march_timer->singleShot(1000, this, SLOT(getsRemoved()));
}

void Goblin::march() {
    QLineF path(pos(), next_point);

    if (path.length() < 5) {
        point_index++;
        if (next_point == way_points.back()) {
            march_timer->stop();
            game->lostHp(damage);
            QSound::play(":/Resource/Background/Lose_Life.wav");
            game->removeItem(this);
            return;
        }
        if (point_index < way_points.size() - 1) {
            next_point = way_points[point_index + 1];
        }
    }

    if (path.angle() >= 135 && path.angle() < 225) {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Left.png"));
    } else if (path.angle() < 45 || path.angle() >= 315) {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Right.png"));
    } else if (path.angle() >= 45 && path.angle() < 135) {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Back.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Goblin/Front.png"));
    }

    double dy = (-1) * speed * qSin(qDegreesToRadians(path.angle()));
    double dx = speed * qCos(qDegreesToRadians(path.angle()));

    setPos(x() + dx, y() + dy);
}


Juggernaut::Juggernaut(QList<QPointF> way_points) {
    setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_left.png"));

    setWayPoint(way_points);
    setPos(way_points[0] - QPointF(60, 60));
    next_point = way_points[1] - QPointF(90, 60);

    speed = 0.3;
    hp = 150;
    damage = 3;
    bounty = 50;
}

void Juggernaut::dies() {
    game->gold += bounty;
    died = true;

    march_timer->stop();

    QLineF path(pos(), next_point);
    if (path.angle() >= 90 && path.angle() < 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_dead_left.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_dead_right.png"));
    }

    QSound::play(":/Resource/Enemy/Juggernaut/Dead.wav");

    march_timer->singleShot(1000, this, SLOT(getsRemoved()));
}

void Juggernaut::setWayPoint(QList<QPointF> way_points_) {
    for(int i = 0; i < way_points_.size(); i++) {
        QPointF adjust(30, 50);
        way_points.append(way_points_[i] - adjust);
    }
}

void Juggernaut::march(){
    QLineF path(pos(), next_point);

    if (path.length() < 5) {
        point_index++;
        if (next_point == way_points.back()) {
            march_timer->stop();
            game->lostHp(damage);
            QSound::play(":/Resource/Background/Lose_Life.wav");
            game->removeItem(this);
            return;
        }
        if (point_index < way_points.size() - 1) {
            next_point = way_points[point_index + 1];
        }
    }

    if (path.angle() >= 135 && path.angle() < 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_left.png"));
    } else if (path.angle() < 45 || path.angle() >= 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_right.png"));
    } else if (path.angle() >= 45 && path.angle() < 135) {
        setPixmap(QPixmap(":/Resource/Enemy/Juggernaut/Jug_back.png"));
    }

    double dy = (-1) * speed * qSin(qDegreesToRadians(path.angle()));
    double dx = speed * qCos(qDegreesToRadians(path.angle()));

    setPos(x() + dx, y() + dy);
}


Orc::Orc(QList<QPointF> way_points) {
    setPixmap(QPixmap(":/Resource/Enemy/Orc/Left.png"));

    setWayPoint(way_points);
    setPos(way_points[0] - QPointF(20, 20));
    next_point = way_points[1];

    speed = 0.7;
    hp = 50;
    damage = 1;
    bounty = 20;
}

void Orc::dies() {
    game->gold += bounty;
    died = true;

    march_timer->stop();

    QLineF path(pos(), next_point);
    if (path.angle() >= 90 && path.angle() < 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Dead_Left.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Dead_Right.png"));
    }

    QSound::play(":/Resource/Enemy/Orc/Dead.wav");

    march_timer->singleShot(1000, this, SLOT(getsRemoved()));
}

void Orc::march(){
    QLineF path(pos(), next_point);

    if (path.length() < 5) {
        if (next_point == way_points.back()) {
            march_timer->stop();
            game->lostHp(damage);
            QSound::play(":/Resource/Background/Lose_Life.wav");
            game->removeItem(this);
            return;
        }
        if (point_index < way_points.size() - 1) {
            point_index++;
            next_point = way_points[point_index + 1];
        }
    }

    if (path.angle() >= 135 && path.angle() < 225) {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Left.png"));
    } else if (path.angle() < 45 || path.angle() >= 315) {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Right.png"));
    } else if (path.angle() >= 45 && path.angle() < 135) {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Back.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Orc/Front.png"));
    }

    double dy = (-1) * speed * qSin(qDegreesToRadians(path.angle()));
    double dx = speed * qCos(qDegreesToRadians(path.angle()));

    setPos(x() + dx, y() + dy);
}


Troll::Troll(QList<QPointF> way_points) {
    setPixmap(QPixmap(":/Resource/Enemy/Troll/Left.png"));

    setWayPoint(way_points);
    setPos(way_points[0] - QPointF(20, 20));
    next_point = way_points[1];

    speed = 0.5;
    hp  = 70;
    damage = 2;
    bounty = 25;
}

void Troll::dies() {
    game->gold += bounty;
    died = true;

    march_timer->stop();

    QLineF path(pos(), next_point);
    if (path.angle() >= 90 && path.angle() < 270) {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Dead_Left.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Dead_Right.png"));
    }

    QSound::play(":/Resource/Enemy/Troll/Dead.wav");

    march_timer->singleShot(1000, this, SLOT(getsRemoved()));
}

void Troll::march() {
    QLineF path(pos(), next_point);

    if (path.length() < 5) {
        point_index++;
        if (next_point == way_points.back()) {
            march_timer->stop();
            game->lostHp(damage);
            QSound::play(":/Resource/Background/Lose_Life.wav");
            game->removeItem(this);
            return;
        }
        if (point_index < way_points.size() - 1) {
            next_point = way_points[point_index + 1];
        }
    }

    if (path.angle() >= 135 && path.angle() < 225) {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Left.png"));
    } else if (path.angle() < 45 || path.angle() >= 315) {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Right.png"));
    } else if (path.angle() >= 45 && path.angle() < 135) {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Back.png"));
    } else {
        setPixmap(QPixmap(":/Resource/Enemy/Troll/Front.png"));
    }

    double dy = (-1) * speed * qSin(qDegreesToRadians(path.angle()));
    double dx = speed * qCos(qDegreesToRadians(path.angle()));

    setPos(x() + dx, y() + dy);
}
