//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_IMPACTONCOURSE_H
#define INC_4_WORMS_IMPACTONCOURSE_H


#include <vector>
#include "Observer.h"
#include "GameTurnState.h"

namespace Worms {
    class ImpactOnCourse : public GameTurnState {
    public:
        ImpactOnCourse();
        ~ImpactOnCourse() = default;

        void endTurn(GameTurn &gt) override;
        void wormHit(GameTurn &gt, uint8_t wormId) override;
        void wormEndHit(GameTurn &gt, uint8_t wormId) override;
        void wormDrowning(GameTurn &gt, uint8_t wormId) override;
        void wormDrowned(GameTurn &gt, uint8_t wormId) override;
        uint8_t getWormToFollow() const;
        std::vector<uint8_t> & getWormsHit();
        void impactNotEnded();

    private:
        std::vector<uint8_t> wormsStillHit;
        std::vector<uint8_t> wormsDrowning;
        std::vector<uint8_t> wormsHit;
        uint8_t wormToFollow{0};
        bool impactEnded{false};
    };
}


#endif //INC_4_WORMS_IMPACTONCOURSE_H
