#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QGraphicsSceneMouseEvent>

#include "elements.hpp"

namespace elements {
    
class BuildButton : public DefaultToolbarButton {
public:
    BuildButton(QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

}

#endif // TOOLBAR_H
