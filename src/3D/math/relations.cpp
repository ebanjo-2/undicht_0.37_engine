#include "relations.h"
#include <iostream>

namespace undicht {


       //////////////////////////////// point-plane relations //////////////////////////////////


    bool pointOnPlane(const glm::vec3& point, const Plane& plane) {
        /** @return whether the point is on the plane or not */

        return pointOnPlane(point, plane.getPoint(), plane.getNormal());
    }

    bool pointOnPlane(const glm::vec3& point, const glm::vec3& point_on_plane, const glm::vec3& plane_normal) {

        return (glm::dot(point - point_on_plane, plane_normal) == 0);
    }



    float distancePointPlane(const glm::vec3& point, const Plane& plane) {
        /** @return the distance between the point and the plane */

        return distancePointPlane(point, plane.getPoint(), plane.getNormal());
    }


    float distancePointPlane(const glm::vec3& point, const glm::vec3& point_on_plane, const glm::vec3& plane_normal) {

        return glm::dot(plane_normal, (point - point_on_plane));
    }


        //////////////////////////////// line-plane relations ///////////////////////////////////


    bool intersecPlaneLine(const Plane& plane, const Line& line, glm::vec3& point) {
        /** @return whether the line and the plane intersect at a single point
        * @param point: where they intersect */

        return intersecPlaneLine(plane.getPoint(), plane.getNormal(), line.getPoint(), line.getDir(), point);
    }

    bool intersecPlaneLine(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_line, const glm::vec3& line_direction, glm::vec3& point) {

        return intersecPlaneLine(glm::dot(plane_normal, point_on_plane), point_on_plane, plane_normal, point_on_line, line_direction, point);
    }


    bool intersecPlaneLine(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_line, const glm::vec3& line_direction, glm::vec3& point) {
        /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
        * may be provided here so that it only needs to be calculated once */

        float x;
        bool intersec = intersecPlaneLine(ppoint_dot_pnorm, point_on_plane, plane_normal, point_on_line, line_direction, x);

        if(!intersec) {

            return false;
        }

        point = point_on_line + line_direction * x;

        return true;
    }



    bool intersecPlaneLine(const Plane& plane, const Line& line, float& dir_factor) {
        /** @return whether the line and the plane intersect at a single point
        @param dir_factor: the factor with which the direction vector of the line has to be multiplied
        * to get from the lines base point to the intersection whith the polygons plane */

        return intersecPlaneLine(plane.getPoint(), plane.getNormal(), line.getPoint(), line.getDir(), dir_factor);
    }

    bool intersecPlaneLine(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_line, const glm::vec3& line_direction, float& dir_factor) {

        return intersecPlaneLine(glm::dot(plane_normal, point_on_plane), point_on_plane, plane_normal, point_on_line, line_direction, dir_factor);
    }


    bool intersecPlaneLine(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_line, const glm::vec3& line_direction, float& dir_factor) {
        /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
        * may be provided here so that it only needs to be calculated once */

        if(!intersecPlaneLine(point_on_plane, plane_normal, point_on_line, line_direction)) {
            // parallel, no or infinite shared points
            return false;
        }

        // dot(plane.getNormal(), line.getPoint() + line.getDir() * x - plane.getPoint()) == 0;
        // n * (ls + ld * x - pp) = 0
        // n * ls + n * ld * x - pp * n = 0
        // (n * ld) * x = (pp * n - n * ls)
        // x = (pp * n - n * ls) / (n * ld); right?

        dir_factor = (ppoint_dot_pnorm - glm::dot(plane_normal, point_on_line)) / glm::dot(plane_normal, line_direction);

        return true;
    }


    bool intersecPlaneLine(const Plane& plane, const Line& line) {
        /** @return whether the line and the plane intersect at a single point */

        // 0 if there is a 90 degree angle between them -> the line is parallel to the plane
        return glm::dot(line.getDir(), plane.getNormal());
    }

    bool intersecPlaneLine(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_line, const glm::vec3& line_direction) {
        /** @return whether the line and the plane intersect at a single point */

        // 0 if there is a 90 degree angle between them -> the line is parallel to the plane
        return glm::dot(line_direction, plane_normal);
    }

    ///////////////////////////////////////////// plane - plane relations /////////////////////////////////////


    bool intersecPlanePlane(const Plane& plane1, const Plane& plane2, Line& intersection) {
        /** calculates the line along which the planes intersect
        * @return false, if the planes are parallel */

        glm::vec3 line_point;
        glm::vec3 line_dir;

        bool intersec = intersecPlanePlane(plane1.getPoint(), plane1.getNormal(), plane2.getPoint(), plane2.getNormal(), line_point, line_dir);

        intersection.def(line_point, line_dir);

        return intersec;
    }

    bool intersecPlanePlane(const glm::vec3& point_on_plane1, const glm::vec3& plane1_normal, const glm::vec3& point_on_plane2, const glm::vec3& plane2_normal, glm::vec3& point_on_line, glm::vec3& line_direction) {


        line_direction = glm::cross(plane1_normal, plane2_normal); // a vector parallel to both planes

        // length is 0 if the planes are parallel
        if(!glm::length(line_direction)) {

            return false;
        }

        // a line on the first plane intersecting with the second one to get a point shared between the planes

        intersecPlaneLine(point_on_plane2, plane2_normal, point_on_plane1, glm::cross(plane1_normal, line_direction), point_on_line);

        return true;
    }


} // undicht
