#ifndef RELATIONS_H
#define RELATIONS_H


#include "plane.h"
#include "line.h"

/// functions to test for the relations between mathematical objects

namespace undicht {

    //////////////////////////////// point-plane relations //////////////////////////////////

    /** @return whether the point is on the plane or not */
    bool pointOnPlane(const glm::vec3& point, const Plane& plane);

    /** @return the distance between the point and the plane */
    float distancePointPlane(const glm::vec3& point, const Plane& plane);

    //////////////////////////////// line-plane relations ///////////////////////////////////

    /** @return whether the line and the plane intersect at a single point
    * @param point: where they intersect */
    bool intersecPlaneLine(const Plane& plane, const Line& line, glm::vec3& point);

    /** @return whether the line and the plane intersect at a single point
    @param dir_factor: the factor with which the direction vector of the line has to be multiplied
    * to get from the lines base point to the intersection whith the polygons plane */
    bool intersecPlaneLine(const Plane& plane, const Line& line, float& dir_factor);

    /** @return whether the line and the plane intersect at a single point */
    bool intersecPlaneLine(const Plane& plane, const Line& line);




} // undicht

#endif // RELATIONS_H
