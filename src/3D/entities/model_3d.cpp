#include "model_3d.h"


namespace undicht {

    Model3D::Model3D() {
        //ctor
    }

    Model3D::~Model3D() {
        //dtor
    }

    void Model3D::setScale(const glm::vec3& scale) {

        m_scale = scale;
    }


    const glm::vec3& Model3D::getScale() {

        return m_scale;
    }

    Model3D& Model3D::addChildModel() {
        /** @return a model that has an orientation relative to this model */

        m_child_models.emplace_back(Model3D());
        m_child_models.back().setTransfRelTo(this);

        return m_child_models.back();
    }


} // undicht

