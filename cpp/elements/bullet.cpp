#include <QTimer>
#include <QTransform>

#include <qmath.h>

#include "bullet.hpp"

namespace elements {

BulletElement::BulletElement(QGraphicsItem *parent) : QObject(), DefaultElement(parent) {
    QTransform transform;
    transform.rotate(90);

    QPixmap pixmap(":/images/arrow.png");
    pixmap = pixmap.scaled(17, 75);
    pixmap = pixmap.transformed(transform);

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