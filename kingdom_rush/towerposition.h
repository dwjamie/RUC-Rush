#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QPixmap>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QGraphicsItem>

class TowerPosition : public QGraphicsPixmapItem {
public:
    TowerPosition(QPointF pos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    friend class Game;
};

#endif // TOWERPOSITION_H
