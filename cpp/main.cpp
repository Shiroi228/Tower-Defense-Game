#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "elements/game.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSharedPointer<elements::GameView> game = elements::GameView::instance();
    game->show();

    return a.exec();
}
