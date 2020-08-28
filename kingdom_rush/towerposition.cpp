#include "towerposition.h"
#include "game.h"
#include "tower.h"

extern Game *game;

TowerPosition::TowerPosition(QPointF pos) {
    setPos(pos);
    setPixmap(QPixmap(":/Resource/Tower/Base.png"));
}

void TowerPosition::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->contains(event->pos())) {
        if (game->build){
            game->build->setPos(pos() - QPointF(13, 35));
            game->build->attack_area->setPos(pos());
            game->gold -= game->build->price;
            game->scene->addItem(game->build);
            game->scene->addItem(game->build->attack_area);

            Archer *archer = dynamic_cast<Archer *>(game->build);
            Artillery *artillery = dynamic_cast<Artillery *>(game->build);
            Mage *mage = dynamic_cast<Mage *>(game->build);

            if (archer) {
                QSound::play(":/Resource/Tower/Archer/Build.wav");
            } else if (artillery) {
                QSound::play(":/Resource/Tower/Artillery/Build.wav");
            } else if (mage) {
                QSound::play(":/Resource/Tower/Mage/Build.wav");
            }

            if (mage && mage->level == 2) {
                game->build->setPos(pos() - QPointF(100, 100));
            }

            game->scene->removeItem(game->cursor);
            game->cursor = nullptr;
            game->build = nullptr;
        }
    }
}
