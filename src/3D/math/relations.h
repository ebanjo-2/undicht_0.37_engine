#ifndef RELATIONS_H
#define RELATIONS_H


#include "plane.h"
#include "ray.h"

/// functions to test for the relations between mathematical objects

namespace undicht {

    //////////////////////////////// point-plane relations //////////////////////////////////

    /** @return whether the point is on the plane or not */
    bool pointOnPlane(const glm::vec3& point, const Plane& plane);

    bool pointOnPlane(const glm::vec3& point, const glm::vec3& point_on_plane, const glm::vec3& plane_normal);

    /** @return the distance between the point and the plane */
    float distancePointPlane(const glm::vec3& point, const Plane& plane);

    float distancePointPlane(const glm::vec3& point, const glm::vec3& point_on_plane, const glm::vec3& plane_normal);

    //////////////////////////////// Ray-plane relations ///////////////////////////////////

    /** @return whether the Ray and the plane intersect at a single point
    * @param point: where they intersect */
    bool intersecPlaneRay(const Plane& plane, const Ray& ray, glm::vec3& point);

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, glm::vec3& point);


    /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
    * may be provided here so that it only needs to be calculated once */
    bool intersecPlaneRay(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, glm::vec3& point);

    /** @return whether the Ray and the plane intersect at a single point
    @param dir_factor: the factor with which the direction vector of the Ray has to be multiplied
    * to get from the Rays base point to the intersection whith the polygons plane */
    bool intersecPlaneRay(const Plane& plane, const Ray& ray, float& dir_factor);

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, float& dir_factor);


    /** @param ppoint_dot_pnorm: if the plane gets used a lot for collision detection, the dot product between its normal and point
    * may be provided here so that it only needs to be calculated once */
    bool intersecPlaneRay(float ppoint_dot_pnorm, const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction, float& dir_factor);

    /** @return whether the Ray and the plane intersect at a single point */
    bool intersecPlaneRay(const Plane& plane, const Ray& ray);

    bool intersecPlaneRay(const glm::vec3& point_on_plane, const glm::vec3& plane_normal, const glm::vec3& point_on_ray, const glm::vec3& ray_direction);


    ///////////////////////////////////////////// plane - plane relations /////////////////////////////////////

    /** calculates the Ray along which the planes intersect
    * @return false, if the planes are parallel */
    bool intersecPlanePlane(const Plane& plane1, const Plane& plane2, Ray& intersection);

    bool intersecPlanePlane(const glm::vec3& point_on_plane1, const glm::vec3& plane1_normal, const glm::vec3& point_on_plane2, const glm::vec3& plane2_normal, glm::vec3& point_on_ray, glm::vec3& ray_direction);

} // undicht

#endif // RELATIONS_H
