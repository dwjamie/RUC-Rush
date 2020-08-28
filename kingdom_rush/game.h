#ifndef GAME_H
#define GAME_H

#include "towerposition.h"
#include "towericon.h"
#include <QGraphicsView>
#include <QSound>

class Tower;
class Enemy;

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game();
    ~Game();
    QGraphicsScene *scene;
    void lostHp(int damage);
    void gameOver();
    void loadWayPoints();
    void loadTowerPositions();
    void loadIcon();
    void loadText();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void removeItem(QGraphicsItem *item);
    void clearScene(QGraphicsItem *pic);

    friend class TowerPosition;
    friend class Tower;
    friend class Archer;
    friend class Artillery;
    friend class Mage;
    friend class ArcherIcon;
    friend class MageIcon;
    friend class ArtilleryIcon;
    friend class Goblin;
    friend class Juggernaut;
    friend class Orc;
    friend class Troll;

public slots:
    void addEnemy();
    void Add_Waves();
    void setText();
    void next_wave();
    void gameWin();
    void enterNextStage();

private:
    int stage;
    int hp;
    int gold;
    int enemy_left;
    int num_of_waves;
    int Enemy_order;
    int wave_order;
    int wave_enemy_number;
    QList<Enemy *> wave;
    QTimer *inwave_timer;
    QTimer *waves_timer;
    QTimer *game_win_timer;

    QGraphicsSimpleTextItem *hp_;
    QGraphicsSimpleTextItem *gold_;
    QGraphicsSimpleTextItem *wave_;
    QGraphicsPixmapItem *game_win_pic;
    QGraphicsPixmapItem *game_over_pic;
    QList<QPointF> way_points_1;
    QList<QPointF> way_points_2_1;
    QList<QPointF> way_points_2_2;
    ArcherIcon *archericon;
    ArtilleryIcon *artilleryicon;
    MageIcon *mageicon;
    Tower *build;
    QGraphicsPixmapItem *cursor;
    QSound *BGM;
    QList<TowerPosition *> tower_positions;
};

#endif // GAME_H
