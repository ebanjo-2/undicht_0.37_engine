#include "forward_renderer.h"


namespace undicht {

    ForwardRenderer::ForwardRenderer() {
        //ctor
    }

    ForwardRenderer::~ForwardRenderer() {
        //dtor
    }

    void ForwardRenderer::drawModel(Model3D& model) {
        /** draws the model with its child models to the scene framebuffer */

        if(model.getMesh().getSize()) {

            submit(&model.getMesh());

            m_shader.loadTexture(model.getTexture());

            loadModelOrientation(model);
            loadModelScale(model.getWorldScale());

            draw();

        }

        // drawing sub models
        for(Model3D& m : model.m_child_models) {

            drawModel(m);
        }

    }


} // undicht
