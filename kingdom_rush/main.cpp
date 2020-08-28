#include "game.h"
#include <QApplication>

extern Game *game;
Game *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    game = new Game;
    game->show();

    return a.exec();
}
