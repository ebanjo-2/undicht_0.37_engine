#ifndef FORWARD_RENDERER_H
#define FORWARD_RENDERER_H

#include <3D/renderer_3d.h>
#include <3D/entities/model_3d.h>


namespace undicht {


    class ForwardRenderer : public Renderer3D {
        public:

            /** draws the model with its child models to the scene framebuffer */
            void drawModel(Model3D& model);

            ForwardRenderer();
            virtual ~ForwardRenderer();

    };


} // undicht

#endif // FORWARD_RENDERER_H
