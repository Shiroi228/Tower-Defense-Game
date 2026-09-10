#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

namespace elements {
    
class DefaultElement : public QGraphicsPixmapItem {
public:
    DefaultElement(QGraphicsItem *parent = nullptr) : QGraphicsPixmapItem(parent) {};
};

class TextElement : public QGraphicsTextItem {
public:
    TextElement(QGraphicsItem *parent = nullptr) : QGraphicsTextItem(parent) {};
};

}

#endif // ELEMENTS_H
