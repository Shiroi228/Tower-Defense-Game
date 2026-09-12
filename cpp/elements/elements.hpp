#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

namespace elements {

/*
 * DefaultElement
 *
 ***/
    
class DefaultElement : public QGraphicsPixmapItem {
public:
    DefaultElement(QGraphicsItem *parent = nullptr) : QGraphicsPixmapItem(parent) {};
};


/*
 * TextElement
 *
 ***/
class TextElement : public QGraphicsTextItem {
public:
    TextElement(QGraphicsItem *parent = nullptr) : QGraphicsTextItem(parent) {};
};

}

#endif // ELEMENTS_H
