#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPolygonItem>
#include <QPointF>
#include <QObject>

#include "elements.hpp"

namespace elements {
    
class TowerElement : public QObject, public DefaultElement {
    Q_OBJECT
public:
    TowerElement(QGraphicsItem *parent = nullptr);
    
    void fire();

public slots:
    void aquireTarget();

private:
    double distanceTo(QGraphicsItem *target);

private:
    QGraphicsPolygonItem *attackArea_;
    QPointF attackDest_;
    bool hasTarget_;
};

}

#endif // TOWER_H
