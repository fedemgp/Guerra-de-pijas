#ifndef STAGEELEMSHORTGIRDER_H
#define STAGEELEMSHORTGIRDER_H

#include <stageelement.h>

class StageElemShortGirder : public StageElement {
   public:
    StageElemShortGirder(qreal opacity = 1.0);

    StageElement *clone();
    virtual bool canOverlap(StageElement *other);
    void serialize(StageData &sd);
};

#endif  // STAGEELEMSHORTGIRDER_H
