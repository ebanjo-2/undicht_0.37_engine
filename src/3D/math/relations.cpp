#include "relations.h"

namespace undicht {


       //////////////////////////////// point-plane relations //////////////////////////////////


    bool pointOnPlane(const glm::vec3& point, const Plane& plane) {
        /** @return whether the point is on the plane or not */

        return (glm::dot(point - plane.getPoint(), plane.getNormal()) == 0);
    }


    float distancePointPlane(const glm::vec3& point, const Plane& plane) {
        /** @return the distance between the point and the plane */


        return glm::dot(plane.getNormal(), (point - plane.getPoint()));
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

        point = line.getPoint() + line.getDir() * x;

        return true;
    }


    bool intersecPlaneLine(const Plane& plane, const Line& line, float& dir_factor) {
        /** @return whether the line and the plane intersect at a single point
        @param dir_factor: the factor with which the direction vector of the line has to be multiplied
        * to get from the lines base point to the intersection whith the polygons plane */

        if(glm::dot(line.getDir(), plane.getNormal()) == 0) {
            // parallel, no or infinite shared points
            return false;
        }

        // dot(plane.getNormal(), line.getPoint() + line.getDir() * x - plane.getPoint()) == 0;
        // n * (ls + ld * x - pp) = 0
        // n * ls + n * ld * x - pp * n = 0
        // (n * ld) * x = (pp * n - n * ls)
        // x = (pp * n - n * ls) / (n * ld); right?

        dir_factor = (glm::dot(plane.getPoint(), plane.getNormal()) - glm::dot(plane.getNormal(), line.getPoint())) / glm::dot(plane.getNormal(), line.getDir());

        return true;
    }

    bool intersecPlaneLine(const Plane& plane, const Line& line) {
        /** @return whether the line and the plane intersect at a single point */

        if(glm::dot(line.getDir(), plane.getNormal()) == 0) {
            // parallel, no or infinite shared points
            return false;
        } else {

            return true;
        }

    }


} // undicht
