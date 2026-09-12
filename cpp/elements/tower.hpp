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

public slots:
    void attackTarget();

private:
    QGraphicsPolygonItem *attackArea_;
    QPointF attackDest_;
};

}

#endif // TOWER_H
