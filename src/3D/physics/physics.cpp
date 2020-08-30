#include "physics.h"
#include <iostream>

#include <3D/physics/collision_detection.h>

namespace undicht {


    Physics::Physics() {
        //ctor
    }

    Physics::~Physics() {
        //dtor
    }


    //////////////////////////////////// functions to test for the collision between hitboxes ////////////////////////////////////////

    bool Physics::collision(Hitbox& h1, Hitbox& h2) {

        if((h1.getType() == UND_CUBOID_HITBOX) && (h2.getType() == UND_CUBOID_HITBOX)) {

            return CollisionDetection::overlappingVolume(*(CuboidHitbox*)&h1, *(CuboidHitbox*)&h2);

        } else if ((h1.getType() == UND_SIMPLE_POLYGON_HITBOX) && (h2.getType() == UND_SIMPLE_POLYGON_HITBOX)) {

            return CollisionDetection::overlappingVolume(*(SimplePolygonHitbox*)&h1, *(SimplePolygonHitbox*)&h2);

        } else if ((h1.getType() == UND_SPHERE_HITBOX) && (h2.getType() == UND_SPHERE_HITBOX)) {

            return CollisionDetection::overlappingVolume(*(SphereHitbox*)&h1, *(SphereHitbox*)&h2);

        }  else if ((h1.getType() == UND_POLYGON_HITBOX) && (h2.getType() == UND_POLYGON_HITBOX)) {

            return CollisionDetection::overlappingVolume(*(PolygonHitbox*)&h1, *(PolygonHitbox*)&h2);
        }

        // no known collision detection
        return false;
    }


} // undicht
