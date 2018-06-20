#ifndef GIRDER_H_
#define GIRDER_H_

#include "Physics.h"
#include "PhysicsEntity.h"
#include "Stage.h"

namespace Worms {
class Girder : public PhysicsEntity {
   public:
    const float angle;

    Girder(const Worms::GirderData &data, Physics &physics);
    Girder(Girder &copy) = delete;
    ~Girder() = default;
};
}  // namespace Worms

#endif
