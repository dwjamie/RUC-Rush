#include "game.h"
#include "tower.h"

extern Game *game;

Game::Game() {
    stage = 1;
    gold = 200;
    hp = 10;

    enemy_left = 18;
    num_of_waves = 4;

    Enemy_order=0;
    wave_order = 0;

    wave_enemy_number=0;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1280, 720);

    setScene(scene);

    cursor = nullptr;
    build = nullptr;
    setMouseTracking(true);

    QGraphicsPixmapItem *backgroundpic = new QGraphicsPixmapItem;
    backgroundpic->setPixmap(QPixmap(":/Resource/Background/Stage_1.png").
                             scaled(1280, 720, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    scene->addItem(backgroundpic);

    BGM = new QSound(":/Resource/Background/BGM_1.wav");
    BGM->setLoops(-1);
    BGM->play();

    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    loadTowerPositions();
    loadWayPoints();
    loadIcon();
    loadText();

    Add_Waves();

    game_win_timer  = new QTimer;
    connect(game_win_timer, SIGNAL(timeout()), this, SLOT(gameWin()));
    game_win_timer->start(10);
}

Game::~Game() {
}

void Game::lostHp(int damage) {
    hp -= damage;
    if (hp <= 0) {
        gameOver();
    }
}

void Game::gameWin() {
    if (!enemy_left) {
        game_win_timer->stop();

        BGM->stop();
        QSound::play(":/Resource/Background/Game_Win.wav");

        game_win_pic = new QGraphicsPixmapItem;
        game_win_pic->setPixmap(QPixmap(":/Resource/Background/Victory.png").scaled(1280, 720, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        scene->addItem(game_win_pic);

        clearScene(game_win_pic);

        if (stage == 1) {
            QTimer *timer = new QTimer;
            timer->singleShot(5000, this, SLOT(enterNextStage()));
        }
    }
}

void Game::gameOver() {
    game_win_timer->stop();

    BGM->stop();
    QSound::play(":/Resource/Background/Game_Lose.wav");

    game_over_pic = new QGraphicsPixmapItem;
    game_over_pic->setPixmap(QPixmap(":/Resource/Background/Defeat.png").scaled(1280, 720, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    scene->addItem(game_over_pic);

    clearScene(game_over_pic);
}

void Game::loadWayPoints() {
    double c = 2.0 / 3.0;//scale
//关卡1
    const QPointF wayPoint1 = QPointF(1920*c, 303*c);
    way_points_1.append(wayPoint1);

    const QPointF wayPoint2 = QPointF(1800*c, 303*c);
    way_points_1.append(wayPoint2);

    const QPointF wayPoint3 = QPointF(1634*c, 377*c);
    way_points_1.append(wayPoint3);

    const QPointF wayPoint4 = QPointF(1275*c, 364*c);
    way_points_1.append(wayPoint4);

    const QPointF wayPoint5 = QPointF(1190*c, 172*c);
    way_points_1.append(wayPoint5);

    const QPointF wayPoint6 = QPointF(1039*c, 172*c);
    way_points_1.append(wayPoint6);

    const QPointF wayPoint7 = QPointF(957*c, 373*c);
    way_points_1.append(wayPoint7);

    const QPointF wayPoint8 = QPointF(665*c, 408*c);
    way_points_1.append(wayPoint8);

    const QPointF wayPoint9 = QPointF(665*c, 585*c);
    way_points_1.append(wayPoint9);

    const QPointF wayPoint10 = QPointF(1090*c, 585*c);
    way_points_1.append(wayPoint10);

    const QPointF wayPoint11 = QPointF(1152*c, 658*c);
    way_points_1.append(wayPoint11);

    const QPointF wayPoint12 = QPointF(1083*c, 775*c);
    way_points_1.append(wayPoint12);

    const QPointF wayPoint13 = QPointF(909*c, 833*c);
    way_points_1.append(wayPoint13);

    const QPointF wayPoint14 = QPointF(909*c, 1080*c);
    way_points_1.append(wayPoint14);

//关卡2，线路1
    const QPointF wayPoint_2_1 = QPointF(1920*c, 283*c);
    way_points_2_1.append(wayPoint_2_1);

    const QPointF wayPoint_2_2 = QPointF(1662*c, 283*c);
    way_points_2_1.append(wayPoint_2_2);

    const QPointF wayPoint_2_3 = QPointF(1168*c, 236*c);
    way_points_2_1.append(wayPoint_2_3);

    const QPointF wayPoint_2_4 = QPointF(770*c, 349*c);
    way_points_2_1.append(wayPoint_2_4);

    const QPointF wayPoint_2_5 = QPointF(914*c, 503*c);
    way_points_2_1.append(wayPoint_2_5);

    const QPointF wayPoint_2_6 = QPointF(1279*c, 692*c);
    way_points_2_1.append(wayPoint_2_6);

    const QPointF wayPoint_2_7 = QPointF(1176*c, 814*c);
    way_points_2_1.append(wayPoint_2_7);

    const QPointF wayPoint_2_8 = QPointF(656*c, 659*c);
    way_points_2_1.append(wayPoint_2_8);

    const QPointF wayPoint_2_9 = QPointF(0*c, 659*c);
    way_points_2_1.append(wayPoint_2_9);

//关卡2，线路2
    const QPointF wayPoint_1_1 = QPointF(1920*c, 517*c);
    way_points_2_2.append(wayPoint_1_1);

    const QPointF wayPoint_1_2 = QPointF(1621*c, 517*c);
    way_points_2_2.append(wayPoint_1_2);

    const QPointF wayPoint_1_3 = QPointF(1187*c, 418*c);
    way_points_2_2.append(wayPoint_1_3);

    way_points_2_2.append(wayPoint_2_5);

    way_points_2_2.append(wayPoint_2_6);

    way_points_2_2.append(wayPoint_2_7);

    way_points_2_2.append(wayPoint_2_8);

    way_points_2_2.append(wayPoint_2_9);
}

void Game::loadTowerPositions() {
    double i = 2.0 / 3.0; // scale

    if (stage == 1) {
        tower_positions.append(new TowerPosition(QPointF(1123*i-50, 274*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1123*i-50, 375*i-24)));

        tower_positions.append(new TowerPosition(QPointF(863*i-50, 276*i-24)));

        tower_positions.append(new TowerPosition(QPointF(785*i-50, 491*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1009*i-50, 666*i-24)));

        tower_positions.append(new TowerPosition(QPointF(857*i-50, 711*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1030*i-50, 881*i-24)));
    } else {
        tower_positions.append(new TowerPosition(QPointF(922*i-50, 159*i-24)));

        tower_positions.append(new TowerPosition(QPointF(789*i-50, 187*i-24)));

        tower_positions.append(new TowerPosition(QPointF(924*i-50, 367*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1069*i-50, 338*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1267*i-50, 333*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1159*i-50, 512*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1126*i-50, 701*i-24)));

        tower_positions.append(new TowerPosition(QPointF(977*i-50, 658*i-24)));

        tower_positions.append(new TowerPosition(QPointF(803*i-50, 592*i-24)));

        tower_positions.append(new TowerPosition(QPointF(1355*i-50, 840*i-24)));

        tower_positions.append(new TowerPosition(QPointF(856*i-50, 855*i-24)));
    }

    for (int i = 0; i < tower_positions.size(); i++) {
        scene->addItem(tower_positions[i]);
    }
}

void Game::loadIcon() {
    archericon = new ArcherIcon(QPointF(50, 100));
    scene->addItem(archericon);

    artilleryicon = new ArtilleryIcon(QPointF(50, 200));
    scene->addItem(artilleryicon);

    mageicon = new MageIcon(QPointF(50, 300));
    scene->addItem(mageicon);
}

void Game::loadText() {
    hp_ = new QGraphicsSimpleTextItem;
    gold_ = new QGraphicsSimpleTextItem;
    wave_ = new QGraphicsSimpleTextItem;

    hp_->setBrush(Qt::white);
    hp_->setFont(QFont("宋体",12));
    hp_->setPos(103, 46);
    gold_->setBrush(Qt::white);
    gold_->setFont(QFont("宋体",12));
    gold_->setPos(170, 46);
    wave_->setBrush(Qt::white);
    wave_->setFont(QFont("宋体",12));
    wave_->setPos(310, 46);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setText()));
    timer->start(10);

    scene->addItem(hp_);
    scene->addItem(gold_);
    scene->addItem(wave_);
}

void Game::setCursor(QString filename) {
    if (cursor) {
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem;
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (cursor){
        cursor->setPos(event->pos());
    }
}

void Game::addEnemy() {
    if (wave_enemy_number == 0) {
        QSound::play(":/Resource/Background/Next_Wave_Ready.wav");
    }

    if (stage == 1) {
        switch (wave_order) {
        case 0:
            wave.append(new Goblin(way_points_1));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 1:
            wave.append(new Orc(way_points_1));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 2:
            wave.append(new Troll(way_points_1));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 3:
            wave.append(new Juggernaut(way_points_1));
            scene->addItem(wave[Enemy_order++]);
        }
    } else {
        switch (wave_order) {
        case 0:
            wave.append(new Goblin(way_points_2_1));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 1:
            wave.append(new Orc(way_points_2_2));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 2:
            wave.append(new Troll(way_points_2_1));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 3:
            wave.append(new Juggernaut(way_points_2_2));
            scene->addItem(wave[Enemy_order++]);
            break;
        case 4:
            wave.append(new Troll(way_points_2_1));
            scene->addItem(wave[Enemy_order++]);
            wave.append(new Juggernaut(way_points_2_2));
            scene->addItem(wave[Enemy_order++]);
        }
    }

    wave_enemy_number++;

    if(wave_enemy_number == 3 + wave_order) {
        inwave_timer->stop();
        waves_timer = new QTimer(this);
        waves_timer->start(20000);
        connect(waves_timer, SIGNAL(timeout()), this, SLOT(next_wave()));
        wave_enemy_number = 0;
    }
}

void Game::next_wave(){
    inwave_timer->start(2000);
    waves_timer->stop();
    wave_order++;
    if(wave_order == num_of_waves)
        inwave_timer->stop();
}

void Game::Add_Waves(){
    inwave_timer = new QTimer(this);
    inwave_timer->start(2000);
    connect(inwave_timer, SIGNAL(timeout()), this, SLOT(addEnemy()));
}

void Game::setText() {
    hp_->setText(QString("%1").arg(hp));
    gold_->setText(QString("%1").arg(gold));

    int current_wave;
    if (wave_order <= 3) {
        current_wave = wave_order + 1;
    } else {
        current_wave = 4;
    }

    wave_->setText(QString("%1 / %2").arg(current_wave).arg(num_of_waves));
}

void Game::removeItem(QGraphicsItem *item) {
    if (dynamic_cast<Enemy *>(item)) {
        enemy_left--;
    }

    delete item;
    item = nullptr;
}

void Game::clearScene(QGraphicsItem *pic) {
    delete inwave_timer;
    inwave_timer = nullptr;

    delete waves_timer;
    waves_timer = nullptr;

    delete game_win_timer;
    game_win_timer = nullptr;

    delete archericon;
    archericon = nullptr;

    delete artilleryicon;
    artilleryicon = nullptr;

    delete mageicon;
    mageicon = nullptr;

    delete build;
    build = nullptr;

    delete cursor;
    cursor = nullptr;

    delete BGM;
    BGM = nullptr;

    wave.clear();

    tower_positions.clear();

    QList<QGraphicsItem *> all_items = pic->collidingItems();

    foreach (QGraphicsItem *item, all_items) {
        scene->removeItem(item);
        item = nullptr;
    }
}

void Game::enterNextStage() {
    stage = 2;
    gold = 200;
    hp = 10;

    enemy_left = 25;
    num_of_waves = 5;

    Enemy_order = 0;
    wave_order = 0;

    wave_enemy_number = 0;

    delete game_win_pic;
    game_win_pic = nullptr;

    cursor = nullptr;
    build = nullptr;
    setMouseTracking(true);

    QGraphicsPixmapItem *backgroundpic = new QGraphicsPixmapItem;
    backgroundpic->setPixmap(QPixmap(":/Resource/Background/Stage_2.png").
                             scaled(1280, 720, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    scene->addItem(backgroundpic);

    BGM = new QSound(":/Resource/Background/BGM_2.wav");
    BGM->setLoops(-1);
    BGM->play();

    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    loadTowerPositions();
    loadWayPoints();
    loadIcon();
    loadText();

    Add_Waves();

    game_win_timer  = new QTimer;
    connect(game_win_timer, SIGNAL(timeout()), this, SLOT(gameWin()));
    game_win_timer->start(10);
}
