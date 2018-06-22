#ifndef STAGEELEMLONGGIRDER_H
#define STAGEELEMLONGGIRDER_H

#include "stageelement.h"

class StageElemLongGirder : public StageElement {
public:
    StageElemLongGirder(qreal opacity = 1.0);

    virtual StageElement *clone();
    virtual bool canOverlap(StageElement *other);
    virtual void serialize(StageData &sd);
};

#endif // STAGEELEMLONGGIRDER_H
