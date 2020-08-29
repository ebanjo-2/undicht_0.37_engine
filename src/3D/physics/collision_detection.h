#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H


#include <3D/physics/hitboxes/cuboid_hitbox.h>
#include <3D/physics/hitboxes/simple_polygon_hitbox.h>
#include <3D/physics/hitboxes/sphere_hitbox.h>


namespace undicht {


    class CollisionDetection {
        /** a class with static functions to test whether the volumes of 3D bodies overlap */

        public:

            static bool overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end);

        public:

            static bool overlappingVolume(const CuboidHitbox& h1, const CuboidHitbox& h2);

            static bool overlappingVolume(const SimplePolygonHitbox& h1, const SimplePolygonHitbox& h2);

            static bool overlappingVolume(const SphereHitbox& h1, const SphereHitbox& h2);

    };


} // undicht

#endif // COLLISION_DETECTION_H
