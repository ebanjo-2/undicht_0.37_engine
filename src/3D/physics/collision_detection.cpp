#include "collision_detection.h"
#include <iostream>


namespace undicht {


    bool CollisionDetection::overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end) {

        // making sure the start of the range is before the end
        float s1 = glm::min(range_1_start, range_1_end);
        float e1 = glm::max(range_1_start, range_1_end);

        float s2 = glm::min(range_2_start, range_2_end);
        float e2 = glm::max(range_2_start, range_2_end);

        // cases in which the ranges do not overlap (is it really that easy ?)
        if((e1 < s2) || (e2 < s1)) {

            return false;
        }

        return true;
    }

    /////////////////////////////////////////////// cuboid hitbox ///////////////////////////////////////////////////////////////

    bool CollisionDetection::overlappingVolume(const CuboidHitbox& h1, const CuboidHitbox& h2) {

        glm::vec3 half_size_1 = h1.getWorldScale() / 2.0f;
        glm::vec3 half_size_2 = h2.getWorldScale() / 2.0f;

        glm::vec3 pos1 = h1.getWorldPosition();
        glm::vec3 pos2 = h2.getWorldPosition();

        if(overlappingRanges(pos1.x - half_size_1.x, pos1.x + half_size_1.x, pos2.x - half_size_2.x, pos2.x + half_size_2.x)) {

            if(overlappingRanges(pos1.y - half_size_1.y, pos1.y + half_size_1.y, pos2.y - half_size_2.y, pos2.y + half_size_2.y)) {

                if(overlappingRanges(pos1.z - half_size_1.z, pos1.z + half_size_1.z, pos2.z - half_size_2.z, pos2.z + half_size_2.z)) {

                    return true;
                }
            }
        }

        return false;
    }

    ///////////////////////////////////////////////////// sphere hitbox /////////////////////////////////////////////////////


    bool CollisionDetection::overlappingVolume(const SphereHitbox& h1, const SphereHitbox& h2) {

        if(glm::length(h1.getWorldPosition() - h2.getWorldPosition()) < ((h1.getWorldScale().x + h2.getWorldScale().x) / 2)) {

            return true;
        }

        return false;
    }

    ///////////////////////////////////////////////////// polygon hitbox /////////////////////////////////////////////////////

    bool CollisionDetection::overlappingVolume(const PolygonHitbox& h1, const PolygonHitbox& h2) {

        return h1.collision(h2);
    }


} // undicht
