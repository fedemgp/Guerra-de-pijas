#include "stageelemlonggirder.h"

StageElemLongGirder::StageElemLongGirder(qreal opacity) :
    StageElement(":/assets/stage/long_girder.png", ItemType::LongGirder, opacity) {
}

StageElement *StageElemLongGirder::clone() {
    auto *e = new StageElemLongGirder;
    e->angle = this->angle;
    e->setRotation(this->angle);
    return e;
}


void StageElemLongGirder::serialize(StageData &sd) {
    sd.addLongGirder(this->getPosition(), this->getAngle());
}

bool StageElemLongGirder::canOverlap(StageElement *other) {
    return (other->getType() != ItemType::Worm);
}
