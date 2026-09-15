#include <QPixmap>
#include <QTimer>

#include "enemy.hpp"

namespace elements {

EnemyElement::EnemyElement(QGraphicsItem *parent) : QObject(), DefaultElement(parent), STEP_SIZE_(5),  pointIndex_(0) {
    QPixmap pixmap(":/images/enemy.png");
    pixmap = pixmap.scaled(100, 100);
    setPixmap(pixmap);

    points_ << QPointF(200, 200) << QPointF(400, 200);
    dest_ = points_[pointIndex_];
    rotateToPoint(dest_);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EnemyElement::moveForward);
    timer->start(150);
}

void EnemyElement::rotateToPoint(const QPointF &point) {
    QLineF line(pos(), point);

    setRotation(-1 * line.angle());
}

void EnemyElement::moveForward() {
    QLineF line(pos(), dest_);
    if (line.length() < 5) {
        pointIndex_++;
        if (pointIndex_ >= points_.size()) { return; }

        dest_ = points_[pointIndex_];
        rotateToPoint(dest_);
    }

    double theta = rotation();

    double dx = STEP_SIZE_ * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE_ * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);
}

}