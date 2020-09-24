#include "plane_hitbox.h"
#include <3D/math/relations.h>


namespace undicht {

    PlaneHitbox::PlaneHitbox() {
        //ctor
    }

    PlaneHitbox::~PlaneHitbox() {
        //dtor
    }

    int PlaneHitbox::getType() const{

        return UND_PLANE_HITBOX;
    }


    ////////////////////////// getting the defining attributes of the plane with the Orientation3D applied //////////////////////////

    glm::vec3 PlaneHitbox::getWorldNormal() const {
        /** @return the normal of the plane (in world space)*/

        return glm::rotate(getWorldRot(), getNormal());
    }

    glm::vec3 PlaneHitbox::getWorldPoint() const {
        /** @return a point on the plane (in world space)*/

        return getWorldPosition() + getPoint();
    }


    ////////////////////////////////////// functions to test for intersections with other hitboxes //////////////////////////////////

    bool PlaneHitbox::intersection(const LineHitbox& line, glm::vec3& point_of_intersection) {

        return intersecPlaneRay(m_norm_dot_point, getWorldPoint(), getWorldNormal(), line.getWorldPoint(), line.getWorldDir(), point_of_intersection);
    }

    bool PlaneHitbox::intersection(const LineHitbox& line, float& dir_factor) {

        return intersecPlaneRay(m_norm_dot_point, getWorldPoint(), getWorldNormal(), line.getWorldPoint(), line.getWorldDir(), dir_factor);
    }

} // undicht
