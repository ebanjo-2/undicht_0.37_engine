#include "collision_detection.h"
#include <iostream>


namespace undicht {

    std::ostream& operator<< (std::ostream& out, const glm::vec3& v) {

        out << v.x << " " << v.y << " " << v.z;

        return out;
    }

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


    ///////////////////////////////////////////////// Polygon Hitbox ////////////////////////////////////////////////////////


    bool CollisionDetection::overlappingVolume(const PolygonHitbox& h1, const PolygonHitbox& h2) {

        for(const SimplePolygonHitbox& simple_hitbox : h1.m_hitboxes) {
            // testing for collision with all simple hitboxes from h2

            if(overlappingVolume(simple_hitbox, h2)) {

                return true;
            }

        }

        return false;
    }

    //////////////////////////////////////// polygon hitbox X simple polygon hitbox ////////////////////////////////////////


    bool CollisionDetection::overlappingVolume(const SimplePolygonHitbox& h1, const PolygonHitbox& h2) {

        return overlappingVolume(h2, h1);
    }

    bool CollisionDetection::overlappingVolume(const PolygonHitbox& h1, const SimplePolygonHitbox& h2) {

        for(const SimplePolygonHitbox& simple_hitbox : h1.m_hitboxes) {
            // testing for collision with all simple hitboxes from h1

            if(overlappingVolume(simple_hitbox, h2)) {

                return true;
            }

        }

        return false;
    }

    /////////////////////////////////////////////// simple polygon hitbox ///////////////////////////////////////////////

    bool CollisionDetection::overlappingVolume(const SimplePolygonHitbox& h1, const SimplePolygonHitbox& h2) {

        // testing if any edges of any of the hitboxes are inside the volume of the other one
        for(const HitboxPolygon& polygon : h1.getPolygons()) {

            if(overlappingVolume(polygon, h2)) {

                return true;
            }

        }

        for(const HitboxPolygon& polygon : h2.getPolygons()) {

            if(overlappingVolume(polygon, h1)) {

                return true;
            }
        }

        return false;
    }

    ////////////////////////////////////// simple polygon hitbox X hitbox polygon //////////////////////////////////////////

    bool CollisionDetection::overlappingVolume(const SimplePolygonHitbox& h1, const HitboxPolygon& polygon) {

        return overlappingVolume(polygon, h1);
    }


    bool CollisionDetection::overlappingVolume(const HitboxPolygon& polygon, const SimplePolygonHitbox& h1) {

        std::vector<glm::vec3> polygon_vertices = polygon.getWorldVertices();
        int poly_size = polygon_vertices.size();

        for(int i = 0; i < poly_size; i++) {
            // testing collision with every edge of the polygon

            if(h1.collision(polygon_vertices.at(i), polygon_vertices.at((i + 1) % poly_size))) {

                // line is inside simple hitbox
                return true;
            }

        }

        return false;
    }

} // undicht
