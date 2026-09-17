#include "toolbar.hpp"
#include "game.hpp"

namespace elements {

BuildButton::BuildButton(QGraphicsItem *parent) : DefaultToolbarButton(parent) {
    QPixmap pixmap(":/images/build.png");
    pixmap.scaled(16, 16);
    
    setPixmap(pixmap);
}

void BuildButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    const QSharedPointer<GameView> &game = GameView::instance();

    if (!game->tower()) {
        game->setTower(new TowerElement());
        
        game->setCursor(":/images/tower.png");
    }
}

}