#include "stageelemshortgirder.h"

StageElemShortGirder::StageElemShortGirder(qreal opacity)
    : StageElement(":/assets/stage/short_girder.png", ItemType::ShortGirder, opacity) {}

StageElement *StageElemShortGirder::clone() {
    auto *e = new StageElemShortGirder;
    e->angle = this->angle;
    e->setRotation(this->angle);
    return e;
}

void StageElemShortGirder::serialize(StageData &sd) {
    sd.addShortGirder(this->getPosition(), this->getAngle());
}

bool StageElemShortGirder::canOverlap(StageElement *other) {
    return (other->getType() != ItemType::Worm);
}
