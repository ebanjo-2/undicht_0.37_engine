#include "plane.h"

namespace undicht {

    Plane::Plane() {
        //ctor
    }

    Plane::Plane(const glm::vec3& point, const glm::vec3& normal) {

        def(point, normal);
    }

    Plane::~Plane() {
        //dtor
    }


    ///////////////////////////////////// functions to define the plane /////////////////////////////////////

    void Plane::def(const glm::vec3& point, const glm::vec3& normal){
        /** defined by a point on the plane + a normal vector */

        m_point = point;
        m_normal = glm::normalize(normal);

    }

    void Plane::def(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3){
        /** defined by 3 points on the plane */

        m_point = point1;
        m_normal = glm::normalize(glm::cross(point2 - point1, point3 - point1));
    }

    void Plane::defW2D(const glm::vec3& point, const glm::vec3& dir1, const glm::vec3& dir2){
        /** defined by a point on the plane + 2 vectors pointing in two directions on the plane */

        m_point = point;
        m_normal = glm::normalize(glm::cross(dir1, dir2));
    }

    ///////////////////////////////////// getting the defining attributes of the plane /////////////////////////////////////

    const glm::vec3& Plane::getNormal() const{
        /** @return the normal of the plane */

        return m_normal;
    }

    const glm::vec3& Plane::getPoint() const{
        /** @return a point on the plane */

        return m_point;
    }


     ///////////////////////////////////// testing whether the plane is properly defined /////////////////////////////////////


    Plane::operator bool() {

        return (glm::length(m_normal) != 0);
    }


} // undicht
