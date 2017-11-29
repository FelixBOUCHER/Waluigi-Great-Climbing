#include <QApplication>
#include "game.h"

Game *G;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    G = new Game();
    G->show();

    return a.exec();
}
