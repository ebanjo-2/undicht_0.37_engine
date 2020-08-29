#include "orientation_3d.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>


namespace undicht {

    Orientation3D::Orientation3D() {
        // ctor
        m_rotation = glm::angleAxis(0.0f, glm::vec3(0,0,-1));
        m_position = glm::vec3(0,0,0);
        m_scale = glm::vec3(1,1,1);
    }



    Orientation3D::~Orientation3D() {
        //dtor
    }


    //////////////////////////////////////////////// functions to update matrices /////////////////////////////////////////////////
    // can be reimplemented by other classes to also update their matrices (i.e. view matrix)

    void Orientation3D::updatePosition() {
        /** called whenever the translation matrix needs to be updated */
        m_transl_mat = glm::translate(glm::mat4(1.0f), m_position);
    }


    void Orientation3D::updateRotation() {

        m_rot_mat = glm::toMat4(getRotation());

    }

    void Orientation3D::updateTransf() {

        if(!m_relative_orientation) {

            m_transf_mat = glm::toMat4(getRotation()) * glm::translate(glm::mat4(1.0f), getPosition());
        } else {
            // scaling the translation by the scale of the parent orientation

            m_transf_mat = glm::toMat4(getRotation()) * glm::translate(glm::mat4(1.0f), m_relative_orientation->getScale() * getPosition());
        }


    }

    //////////////////////////////////////////////// translation ////////////////////////////////////////////////

    void Orientation3D::setPosition(const glm::vec3& position) {

        m_position = position;
        m_update_pos = true;
        m_update_transf = true;

    }


    const glm::vec3& Orientation3D::getPosition() const {

        return m_position;
    }


    const glm::mat4& Orientation3D::getTranslMat() {

        if(m_update_pos) {

            updatePosition();
            m_update_pos = false;
        }

        return m_transl_mat;
    }

    glm::vec3 Orientation3D::getWorldPosition() const{
        /** @return the position relative to the worlds 0,0,0 */

        if(!m_relative_orientation) {

            return m_position;
        } else {

            return m_relative_orientation->getWorldPosition() + glm::rotate(m_relative_orientation->getWorldRot(), m_position);
        }

    }


    glm::mat4 Orientation3D::getWorldTranslMat() {

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


    const glm::quat& Orientation3D::getRotation() const{

        return m_rotation;
    }


    const glm::mat4& Orientation3D::getRotMat() {

        if (m_update_rot) {

            updateRotation();
            m_update_rot = false;
        }

        return m_rot_mat;
    }


    glm::quat Orientation3D::getWorldRot() const{
        /** @return the absolute rotation relative to the world */

        if(!m_relative_orientation) {

            return getRotation();
        } else {

            return m_relative_orientation->getWorldRot() * getRotation();
        }
    }


    glm::mat4 Orientation3D::getWorldRotMat() {

        return glm::toMat4(getWorldRot());
    }

    /////////////////////////////////////// scaling /////////////////////////////////////

    void Orientation3D::setScale(const glm::vec3& scale) {
        /** scaling the translation of child elements + can be used to scale the model */

        m_scale = scale;

    }

    const glm::vec3& Orientation3D::getScale() const {

        return m_scale;
    }

    glm::vec3 Orientation3D::getWorldScale() const{
        // scale multiplied by the scale of the orientations parents

        if(!m_relative_orientation) {

            return m_scale;
        } else {

            return m_relative_orientation->getWorldScale() * m_scale;
        }
    }


    ///////////////////////////////////// transformation (translation + rotation combined) ////////////////////////////////////

    const glm::mat4& Orientation3D::getTransfMat() {

        if(m_update_transf) {

            updateTransf();
            m_update_transf = false;

        }

        return m_transf_mat;
    }


    glm::mat4 Orientation3D::getWorldTransfMat() {
        // the absolute transformation relative to the world

        if(!m_relative_orientation) {

            return getTransfMat();
        } else {

            return m_relative_orientation->getTransfMat() * getTransfMat();
        }

    }

    void Orientation3D::setTransfRelTo(Orientation3D* rel_transf) {
        /** sets this orientations transformation (position + rotation) to be relative to the orientation passed
        * @param : if 0 is passed, the transformation will be relative to the world */

        m_relative_orientation = rel_transf;

    }

} // undicht
