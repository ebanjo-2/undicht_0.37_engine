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


        //////////////////////////////// ray-plane relations ///////////////////////////////////


    bool intersecPlaneRay(const Plane& plane, const Ray& ray, glm::vec3& point) {
        /** @return whether the ray and the plane intersect at a single point
        * @param point: where they intersect */

        return intersecPlaneRay(plane.getPoint(), plane.getNormal(), ray.getPoint(), ray.getDir(), point);
    }

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, glm::vec3& point) {

        return intersecPlaneRay(glm::dot(plane_normal, point_on_plane), point_on_plane, plane_normal, point_on_ray, ray_direction, point);
    }


    bool intersecPlaneRay(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, glm::vec3& point) {
        /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
        * may be provided here so that it only needs to be calculated once */

        float x;
        bool intersec = intersecPlaneRay(ppoint_dot_pnorm, point_on_plane, plane_normal, point_on_ray, ray_direction, x);

        if(!intersec) {

            return false;
        }

        point = point_on_ray + ray_direction * x;

        return true;
    }



    bool intersecPlaneRay(const Plane& plane, const Ray& ray, float& dir_factor) {
        /** @return whether the ray and the plane intersect at a single point
        @param dir_factor: the factor with which the direction vector of the ray has to be multiplied
        * to get from the rays base point to the intersection whith the polygons plane */

        return intersecPlaneRay(plane.getPoint(), plane.getNormal(), ray.getPoint(), ray.getDir(), dir_factor);
    }

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, float& dir_factor) {

        return intersecPlaneRay(glm::dot(plane_normal, point_on_plane), point_on_plane, plane_normal, point_on_ray, ray_direction, dir_factor);
    }


    bool intersecPlaneRay(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, float& dir_factor) {
        /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
        * may be provided here so that it only needs to be calculated once */

        if(!intersecPlaneRay(point_on_plane, plane_normal, point_on_ray, ray_direction)) {
            // parallel, no or infinite shared points
            return false;
        }

        // dot(plane.getNormal(), ray.getPoint() + ray.getDir() * x - plane.getPoint()) == 0;
        // n * (ls + ld * x - pp) = 0
        // n * ls + n * ld * x - pp * n = 0
        // (n * ld) * x = (pp * n - n * ls)
        // x = (pp * n - n * ls) / (n * ld); right?

        dir_factor = (ppoint_dot_pnorm - glm::dot(plane_normal, point_on_ray)) / glm::dot(plane_normal, ray_direction);

        return true;
    }


    bool intersecPlaneRay(const Plane& plane, const Ray& ray) {
        /** @return whether the ray and the plane intersect at a single point */

        // 0 if there is a 90 degree angle between them -> the ray is parallel to the plane
        return glm::dot(ray.getDir(), plane.getNormal());
    }

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction) {
        /** @return whether the ray and the plane intersect at a single point */

        // 0 if there is a 90 degree angle between them -> the ray is parallel to the plane
        return glm::dot(ray_direction, plane_normal);
    }

    ///////////////////////////////////////////// plane - plane relations /////////////////////////////////////


    bool intersecPlanePlane(const Plane& plane1, const Plane& plane2, Ray& intersection) {
        /** calculates the ray along which the planes intersect
        * @return false, if the planes are parallel */

        glm::vec3 ray_point;
        glm::vec3 ray_dir;

        bool intersec = intersecPlanePlane(plane1.getPoint(), plane1.getNormal(), plane2.getPoint(), plane2.getNormal(), ray_point, ray_dir);

        intersection.def(ray_point, ray_dir);

        return intersec;
    }

    bool intersecPlanePlane(const glm::vec3& point_on_plane1, const glm::vec3& plane1_normal, const glm::vec3& point_on_plane2, const glm::vec3& plane2_normal, glm::vec3& point_on_ray, glm::vec3& ray_direction) {


        ray_direction = glm::cross(plane1_normal, plane2_normal); // a vector parallel to both planes

        // length is 0 if the planes are parallel
        if(!glm::length(ray_direction)) {

            return false;
        }

        // a ray on the first plane intersecting with the second one to get a point shared between the planes

        intersecPlaneRay(point_on_plane2, plane2_normal, point_on_plane1, glm::cross(plane1_normal, ray_direction), point_on_ray);

        return true;
    }


} // undicht
