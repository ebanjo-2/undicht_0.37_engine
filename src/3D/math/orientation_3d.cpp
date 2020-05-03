#include "orientation_3d.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


namespace undicht {

    Orientation3D::Orientation3D() {
        //ctor
    }

    Orientation3D::~Orientation3D() {
        //dtor
    }

    //////////////////////////////////////////////// translation ////////////////////////////////////////////////

    void Orientation3D::setPosition(const glm::vec3& position) {

        m_position = position;
        m_update_pos = true;
        m_update_transf = true;

    }


    const glm::vec3& Orientation3D::getPosition() {

        return m_position;
    }


    const glm::mat4& Orientation3D::getTranslMat() {

        if(m_update_pos) {

            m_transl_mat = glm::translate(glm::mat4(1.0f), m_position);

        }

        return m_transl_mat;
    }

    const glm::vec3& Orientation3D::getWorldPosition() {
        /** @return the position relative to the worlds 0,0,0 */

    }


    const glm::mat4& Orientation3D::getWorldTranslMat() {

        return glm::translate(glm::mat4(1.0f), getWorldPosition());
    }


    void Orientation3D::addTranslation(const glm::vec3& v) {
        /** moves the object */

        m_position += v;
        m_update_pos = true;
        m_update_transf = true;

    }



    //////////////////////////////////////////////// rotation ////////////////////////////////////////////////

    void Orientation3D::setRotation(const glm::quat& rot) {

        m_rotation = rot;
        m_update_rot = true;
        m_update_transf = true;

    }


    const glm::quat& Orientation3D::getRotation() {

        return m_rotation;
    }


    const glm::mat4& Orientation3D::getRotMat() {

        if (m_update_rot) {

            m_rot_mat = glm::toMat4(getRotation());
            m_update_rot = false;
        }

        return m_rot_mat;
    }


    const glm::quat& Orientation3D::getWorldRot() {
        /** @return the absolute rotation relative to the world */

    }


    const glm::mat4& Orientation3D::getWorldRotMat() {


    }


    ///////////////////////////////////// transformation (translation + rotation combined) ////////////////////////////////////

    const glm::mat4& Orientation3D::getTransfMat() {

        if(m_update_transf) {

            m_transf_mat = glm::toMat4(getRotation()) * glm::translate(glm::mat4(1.0f), getPosition()) ;
            m_update_transf = false;

        }

        return m_transf_mat;
    }


    const glm::mat4& Orientation3D::getWorldTransfMat() {
        // the absolute transformation relative to the world

    }

    void Orientation3D::setTransfRelTo(Orientation3D* rel_transf) {
        /** sets this orientations transformation (position + rotation) to be relative to the orientation passed
        * @param : if 0 is passed, the transformation will be relative to the world */

        m_relative_orientation = rel_transf;

    }

} // undicht
