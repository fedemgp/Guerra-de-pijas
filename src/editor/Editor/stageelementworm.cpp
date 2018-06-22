#include "stageelement.h"
#include "stageelementworm.h"

StageElementWorm::StageElementWorm() :
    StageElement(":/assets/stage/worm.png", ItemType::Worm) {
}

void StageElementWorm::increaseAngle() {
}

void StageElementWorm::decreaseAngle() {
}

StageElement *StageElementWorm::clone() {
    auto *e = new StageElementWorm;
    e->angle = this->angle;
    return e;
}


void StageElementWorm::serialize(StageData &sd) {
    sd.addWorm(this->getPosition(), this->getAngle());
}
