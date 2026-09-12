#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QTimer>

#include "tower.hpp"
#include "bullet.hpp"
#include "game.hpp"

namespace elements {

TowerElement::TowerElement(QGraphicsItem *parent) : QObject(), DefaultElement(parent) {
    QPixmap pixmap(":/images/tower.png");
    pixmap = pixmap.scaled(100, 100);

    setPixmap(pixmap);

    QVector<QPointF> points;
    points << QPoint(1, 0) << QPoint(2, 0)
           << QPoint(3, 1) << QPoint(3, 2)
           << QPoint(2, 3) << QPoint(1, 3)
           << QPoint(0, 2) << QPoint(0, 1);

    int SCALE_FACTOR = 65;
    for (size_t i = 0, n = points.size(); i < n; ++i) {
        points[i] *= SCALE_FACTOR;
    }

    QPolygonF polygon(points);
    QPointF polyCenter(1.4, 1.4);
    polyCenter *= SCALE_FACTOR;
    polyCenter = mapToScene(polyCenter);
    
    QPointF towerCenter(x() + 44, y() + 44);
    QLineF line(polyCenter, towerCenter);
    
    attackArea_ = new QGraphicsPolygonItem(polygon, this);
    attackArea_->setPos(x() + line.dx(), y() + line.dy());

    QTimer *timer = new QTimer(this);
    
    connect(timer, &QTimer::timeout, this, attackTarget);
    
    timer->start(1000);
}

void TowerElement::attackTarget() {
    QLineF line(QPointF(x() + 44, y() + 44), attackDest_);
    qreal angle = line.angle() * -1;
    
    BulletElement *bullet = new BulletElement();
    bullet->setPos(x() + 44, y() + 44);
    bullet->setRotation(angle);

    GameView::instance()->scene()->addItem(bullet);
    
}

}