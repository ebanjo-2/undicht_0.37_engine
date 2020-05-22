#include "camera_3d.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace undicht {

    Camera3D::Camera3D() {
        //ctor
    }

    Camera3D::~Camera3D() {
        //dtor
    }

    void Camera3D::updateTransf() {

        m_view_mat = glm::toMat4(getRotation()) * glm::translate(glm::mat4(1.0f), -1.0f * getPosition());
        m_transf_mat = glm::toMat4(getRotation()) * glm::translate(glm::mat4(1.0f), getPosition());
    }


    const glm::mat4& Camera3D::getViewMatrix() {

        if(m_update_transf) {

            updateTransf();
            m_update_transf = false;
        }

        return m_view_mat;
    }

} // undicht
