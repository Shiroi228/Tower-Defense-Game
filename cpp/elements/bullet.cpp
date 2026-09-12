// #include <QPointF>
// #include <QPolygonF>
#include <QTimer>

#include <qmath.h>

#include "bullet.hpp"

namespace elements {

BulletElement::BulletElement(QGraphicsItem *parent) : DefaultElement(parent) {
    QPixmap pixmap(":/images/arrow.png");
    pixmap = pixmap.scaled(17, 75);

    setPixmap(pixmap);

    QTimer *mover = new QTimer(this);
    connect(mover, &QTimer::timeout, this, &BulletElement::move);
    mover->start(50);
}

void BulletElement::move() {
    double theta = rotation();

    double dx = STEP_SIZE_ * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE_ * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);
}

}