#include "line.h"
#include <iostream>

namespace undicht {

    Line::Line() {
        //ctor
    }

    Line::Line(const glm::vec3& point, const glm::vec3& dir) {

        def(point, dir);
    }

    Line::~Line() {
        //dtor
    }


    /////////////////////////////////////// defining the line ///////////////////////////////////////

    void Line::def(const glm::vec3& point, const glm::vec3& dir) {
        /** defined by a point on the line + the positive direction of the line */

        m_point = point;
        m_direction = dir;
    }


    //////////////////////////// getting the defining attributes of the line ////////////////////////////

    const glm::vec3& Line::getPoint() const {
        /// you get the point

        return m_point;
    }

    const glm::vec3& Line::getDir() const {
        /** @return the positive direction of the line */

        return m_direction;
    }

    ///////////////////// getting the defining attributes of the line with the Orientation3D applied ///////////////////////

    glm::vec3 Line::getWorldPoint() const {

        return getWorldPosition() + getPoint();
    }

    glm::vec3 Line::getWorldDir() const {

        return glm::rotate(getWorldRot(), getDir());
    }

    ///////////////////////////////////// testing whether the line is properly defined /////////////////////////////////////


    Line::operator bool() {

        return (glm::length(m_direction) != 0);
    }


} // undicht
