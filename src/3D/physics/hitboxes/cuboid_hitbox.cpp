#include "cuboid_hitbox.h"


namespace undicht {

    CuboidHitbox::CuboidHitbox() {
        //ctor
    }

    CuboidHitbox::~CuboidHitbox() {
        //dtor
    }

    int CuboidHitbox::getType() {

        return UND_CUBOID_HITBOX;
    }

} // undicht

