#ifndef BULLET_H
#define BULLET_H

#include <QObject>

#include "elements.hpp"

namespace elements {
    
class BulletElement : public QObject, public DefaultElement {
    Q_OBJECT
public:
    BulletElement(QGraphicsItem *parent = nullptr);

public slots:
    void move();

private:
    const int STEP_SIZE_ = 30;
};

}

#endif // BULLET_H
