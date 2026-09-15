#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QList>
#include <QPointF>

#include "elements.hpp"

namespace elements {
    
class EnemyElement : public QObject, public DefaultElement {
    Q_OBJECT
public:
    EnemyElement(QGraphicsItem *parent = nullptr);
    void rotateToPoint(const QPointF &point);

public slots:
    void moveForward();

private:
    const int STEP_SIZE_;
    int pointIndex_;
    
    QList<QPointF> points_;
    QPointF dest_;
};

}

#endif // ENEMY_H
