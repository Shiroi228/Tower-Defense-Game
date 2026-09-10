#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPolygonItem>

#include "elements.hpp"

namespace elements {
    
class TowerElement : public DefaultElement {
public:
    TowerElement(QGraphicsItem *parent = nullptr);

private:
    QGraphicsPolygonItem *attackArea_;
};

}

#endif // TOWER_H
