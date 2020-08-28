#include "towericon.h"
#include "game.h"
#include "tower.h"

extern Game *game;

TowerIcon::TowerIcon(QPointF pos) {
    setPos(pos);
}

ArcherIcon::ArcherIcon(QPointF pos) : TowerIcon (pos) {
    setPixmap(QPixmap(":/Resource/Tower/Archer/Icon.png"));
}

MageIcon::MageIcon(QPointF pos) : TowerIcon (pos) {
    setPixmap(QPixmap(":/Resource/Tower/Mage/Icon.png"));
}

ArtilleryIcon::ArtilleryIcon(QPointF pos) : TowerIcon (pos) {
    setPixmap(QPixmap(":/Resource/Tower/Artillery/Icon.png"));
}

void ArcherIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!game->build && this->contains(event->pos()) && game->gold >= 70) {
        game->build = new Archer(event->pos());
        game->setCursor(QString(":/Resource/Tower/Archer/Archer_1.png"));
    }
}

void ArtilleryIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!game->build && this->contains(event->pos()) && game->gold >= 100) {
        game->build = new Artillery(event->pos());
        game->setCursor(QString(":/Resource/Tower/Artillery/Artillery_1.png"));
    }
}

void MageIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!game->build && this->contains(event->pos()) && game->gold >= 80) {
        game->build = new Mage(event->pos());
        game->setCursor(QString(":/Resource/Tower/Mage/Mage_1.png"));
    }
}
