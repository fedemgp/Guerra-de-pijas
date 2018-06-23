#ifndef QGRAPHICSITEMLAYER_H
#define QGRAPHICSITEMLAYER_H

#include <QObject>
#include <QGraphicsItem>

class QGraphicsItemLayer : public QGraphicsItem {
public:
    QGraphicsItemLayer();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // QGRAPHICSITEMLAYER_H
