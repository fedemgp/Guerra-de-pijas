#ifndef STAGEELEMENT_H
#define STAGEELEMENT_H

#include <string>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QtDebug>
#include "stagedata.h"

enum class ItemType {
    Worm,
    ShortGirder,
    LongGirder,
};

class StageElement : public QGraphicsPixmapItem {
public:
    StageElement(const std::string &resource, ItemType type);

    ItemType getType();

    qreal getAngle() const;
    QPointF getPosition() const;

    virtual StageElement *clone() = 0;
    virtual bool canOverlap(StageElement *other);

    virtual void increaseAngle();
    virtual void decreaseAngle();

    void setRotationEnabled(bool);

    virtual void serialize(StageData &sd) = 0;

protected:
    QPixmap getResource();
    qreal angle{0.0f};
    ItemType type;

private:
    std::string resource;
};

#endif // STAGEELEMENT_H
