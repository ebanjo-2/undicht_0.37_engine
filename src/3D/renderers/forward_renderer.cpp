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

        submit(&model.getMesh());
        m_shader.loadTexture(model.getTexture());

        loadModelOrientation(model);

        draw();

    }


} // undicht
