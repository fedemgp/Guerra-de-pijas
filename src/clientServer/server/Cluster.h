/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __Cluster_H__
#define __Cluster_H__

#include "Weapon.h"

namespace Weapon{
    class Cluster: public Worms::Weapon{
    public:
        Cluster(float angle);
        ~Cluster() override = default;
        void update(float dt) override;
    };
} // namespace Weapon


#endif //__Cluster_H__
