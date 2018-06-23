#include "qgraphicsitemlayer.h"

QGraphicsItemLayer::QGraphicsItemLayer() : QGraphicsItem(nullptr) {
}

QRectF QGraphicsItemLayer::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void QGraphicsItemLayer::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {
}
