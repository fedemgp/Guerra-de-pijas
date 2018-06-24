#ifndef STAGEELEMENT_H
#define STAGEELEMENT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QWidget>
#include <QtDebug>
#include <string>
#include "stagedata.h"

enum class ItemType {
    Worm,
    ShortGirder,
    LongGirder,
};

class StageElement : public QGraphicsPixmapItem {
   public:
    StageElement(const std::string &resource, ItemType type, qreal opacity);

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
    QPixmap getResource(qreal opacity = 1.0);
    qreal angle{0.0f};
    ItemType type;

   private:
    std::string resource;
};

#endif  // STAGEELEMENT_H
