#ifndef STAGEELEMENTWORM_H
#define STAGEELEMENTWORM_H

#include "stageelement.h"

class StageElementWorm : public StageElement {
   public:
    StageElementWorm(qreal opacity = 1.0);

    virtual StageElement *clone();

    virtual void increaseAngle() override;
    virtual void decreaseAngle() override;
    virtual void serialize(StageData &sd);
};

#endif  // STAGEELEMENTWORM_H
