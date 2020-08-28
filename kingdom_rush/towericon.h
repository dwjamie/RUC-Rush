#ifndef TOWERICON_H
#define TOWERICON_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class TowerIcon : public QGraphicsPixmapItem {
public:
    TowerIcon(QPointF pos);
};

class ArcherIcon : public TowerIcon {
public:
    ArcherIcon(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class MageIcon : public TowerIcon {
public:
    MageIcon(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

class ArtilleryIcon : public TowerIcon {
public:
    ArtilleryIcon(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOWERICON_H
