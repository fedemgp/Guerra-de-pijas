#ifndef QGRAPHICSITEMLAYER_H
#define QGRAPHICSITEMLAYER_H

#include <QGraphicsItem>
#include <QObject>

class QGraphicsItemLayer : public QGraphicsItem {
   public:
    QGraphicsItemLayer();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif  // QGRAPHICSITEMLAYER_H
