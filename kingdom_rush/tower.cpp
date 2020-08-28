#include "tower.h"

extern Game *game;

Tower::Tower(QPointF pos) {
    setPos(pos);
    level = 1;
    target = nullptr;
    attack_rate_timer = new QTimer(this);
    connect(attack_rate_timer, SIGNAL(timeout()), this, SLOT(chooseEnemyToAttack()));
}

void Tower::chooseEnemyToAttack() {
    QList<QGraphicsItem *> items_found = attack_area->collidingItems();
    QList<Enemy *> enemies_found;

    foreach (QGraphicsItem *item, items_found) {
        if (thisIsEnemy(item) && dynamic_cast<Enemy *>(item)->died == false) {
            enemies_found.append(dynamic_cast<Enemy *>(item));
        }
    }

    if (enemies_found.isEmpty()) {
        target = nullptr;
        return;
    }

    if (!enemies_found.contains(target)) {
        target = enemies_found[0];
        for (int i = 1; i < enemies_found.size(); i++) {
            if (enemies_found[i]->getSpawnedOrder() < enemies_found[i - 1]->getSpawnedOrder()) {
                target = enemies_found[i];
            }
        }
    }

    attack();
}

bool Tower::thisIsEnemy(QGraphicsItem *item) const {
    Enemy *enemy = dynamic_cast<Enemy *>(item);
    if (enemy) {
        return true;
    }
    return false;
}

Archer::Archer(QPointF pos) : Tower(pos) {
    price = 70;

    setPixmap(QPixmap(":/Resource/Tower/Archer/Archer_1.png"));

    QPointF adjust(200, 230);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(400, 400)));
    attack_rate_timer->start(700);
}

void Archer::upgrade() {
    level++;
    game->gold -= price;
    setPixmap(QPixmap(":/Resource/Tower/Archer/Archer_2.png"));
    QSound::play(":/Resource/Tower/Archer/Upgrade.wav");

    delete attack_area;
    QPointF adjust(190, 220);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(500, 500)));
    game->scene->addItem(attack_area);
    attack_rate_timer->start(480);
}

void Archer::attack() {
    Arrow *arrow = new Arrow(level);

    arrow->setPos(x() + 44, y() + 44);
    arrow->target = target;

    QLineF path(arrow->pos(), arrow->target->pos());
    arrow->setRotation(path.angle());

    game->scene->addItem(arrow);
}

Artillery::Artillery(QPointF pos) : Tower(pos) {
    price = 100;

    setPixmap(QPixmap(":/Resource/Tower/Artillery/Artillery_1.png"));

    QPointF adjust(145, 180);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(300, 300)));
    attack_rate_timer->start(1500);
}

void Artillery::upgrade() {
    level++;
    game->gold -= price;
    setPixmap(QPixmap(":/Resource/Tower/Artillery/Artillery_2.png"));
    QSound::play(":/Resource/Tower/Artillery/Upgrade.wav");

    delete attack_area;
    QPointF adjust(130, 150);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(400, 400)/*待修改*/));
    game->scene->addItem(attack_area);
    attack_rate_timer->start(1200);
}

void Artillery::attack() {
    Fireball *fireball = new Fireball(level);

    fireball->setPos(x() + 44, y() + 44);
    fireball->target = target;

    QLineF path(fireball->pos(), fireball->target->pos());
    fireball->setRotation(path.angle());

    game->scene->addItem(fireball);
}

Mage::Mage(QPointF pos) : Tower(pos) {
    price = 80;

    setPixmap(QPixmap(":/Resource/Tower/Mage/Mage_1.png"));

    QPointF adjust(220, 250);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(450, 450)));
    attack_rate_timer->start(1800);
}

void Mage::upgrade() {
    level++;
    game->gold -= price;
    setPixmap(QPixmap(":/Resource/Tower/Mage/Mage_2.png"));
    QSound::play(":/Resource/Tower/Mage/Upgrade.wav");

    delete attack_area;
    QPointF adjust(187, 195);
    attack_area = new QGraphicsEllipseItem(QRectF(this->pos() - adjust, QSizeF(500, 500)));
    game->scene->addItem(attack_area);
    attack_rate_timer->start(1600);
}

void Mage::attack() {
    Spell *spell = new Spell(level);

    spell->setPos(x() + 44, y() + 44);
    spell->target = target;

    QLineF path(spell->pos(), spell->target->pos());
    spell->setRotation(path.angle());

    game->scene->addItem(spell);
}

void Archer::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos())) {
        if (event->button() == Qt::LeftButton) {
            if (level == 1 && game->gold >= 70) {
                upgrade();
            };
        } else if (event->button() == Qt::RightButton) {
            game->gold += price * 0.7;
            QSound::play(":/Resource/Tower/Tower_Sell.wav");
            delete attack_area;
            delete this;
        }
    }
}

void Artillery::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos())) {
        if (event->button() == Qt::LeftButton) {
            if (level == 1 && game->gold >= 100) {
                upgrade();
            };
        } else if (event->button() == Qt::RightButton) {
            game->gold += price * 0.7;
            QSound::play(":/Resource/Tower/Tower_Sell.wav");
            delete attack_area;
            delete this;
        }
    }
}

void Mage::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos())) {
        if (event->button() == Qt::LeftButton) {
            if (level == 1 && game->gold >= 80) {
                upgrade();
            };
        } else if (event->button() == Qt::RightButton) {
            game->gold += price * 0.7;
            QSound::play(":/Resource/Tower/Tower_Sell.wav");
            delete attack_area;
            delete this;
        }
    }
}
