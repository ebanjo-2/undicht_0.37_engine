#include "relations.h"
#include <iostream>

namespace undicht {


       //////////////////////////////// point-plane relations //////////////////////////////////


    bool pointOnPlane(const glm::vec3& point, const Plane& plane) {
        /** @return whether the point is on the plane or not */

        return (glm::dot(point - plane.getWorldPoint(), plane.getWorldNormal()) == 0);
    }


    float distancePointPlane(const glm::vec3& point, const Plane& plane) {
        /** @return the distance between the point and the plane */

        return glm::dot(plane.getWorldNormal(), (point - plane.getWorldPoint()));
    }


        //////////////////////////////// line-plane relations ///////////////////////////////////


    bool intersecPlaneLine(const Plane& plane, const Line& line, glm::vec3& point) {
        /** @return whether the line and the plane intersect at a single point
        * @param point: where they intersect */

        float x;
        bool intersec = intersecPlaneLine(plane, line, x);

        if(!intersec) {

            return false;
        }

        point = line.getWorldPoint() + line.getWorldDir() * x;

        return true;
    }


    bool intersecPlaneLine(const Plane& plane, const Line& line, float& dir_factor) {
        /** @return whether the line and the plane intersect at a single point
        @param dir_factor: the factor with which the direction vector of the line has to be multiplied
        * to get from the lines base point to the intersection whith the polygons plane */

        if(!intersecPlaneLine(plane, line)) {
            // parallel, no or infinite shared points
            return false;
        }

        // dot(plane.getNormal(), line.getPoint() + line.getDir() * x - plane.getPoint()) == 0;
        // n * (ls + ld * x - pp) = 0
        // n * ls + n * ld * x - pp * n = 0
        // (n * ld) * x = (pp * n - n * ls)
        // x = (pp * n - n * ls) / (n * ld); right?

        dir_factor = (glm::dot(plane.getWorldPoint(), plane.getWorldNormal()) - glm::dot(plane.getWorldNormal(), line.getWorldPoint())) / glm::dot(plane.getWorldNormal(), line.getWorldDir());

        return true;
    }

    bool intersecPlaneLine(const Plane& plane, const Line& line) {
        /** @return whether the line and the plane intersect at a single point */

        // 0 if there is a 90 degree angle between them -> the line is parallel to the plane
        return glm::dot(line.getWorldDir(), plane.getWorldNormal());
    }


} // undicht
