#ifndef SKETCH_RENDERER_H
#define SKETCH_RENDERER_H

#include <3D/renderer_3d.h>


#include <3D/math/ray.h>
#include <3D/entities/model_3d.h>

#include <graphics/vertex_buffer.h>
#include <graphics/uniform.h>
#include <3D/math/orientation_3d.h>


namespace undicht {

    class SketchRenderer : public Renderer3D {
        /** a renderer that can be used to quickly draw simple geometry
        * mainly for debugging */

        protected:

            graphics::VertexBuffer m_sphere_mesh;
            graphics::VertexBuffer m_cube_mesh;

            graphics::Uniform m_color_uniform;

            Orientation3D m_draw_orientation; // to calculate the orientation of the models to draw

        public:
            // changing the way things are drawn

            void setDrawColor(const glm::vec3& color);

        public:
            // functions to draw simple geometry

            virtual void drawSphere(const glm::vec3& position, const glm::vec3& color = glm::vec3(0.8,0.8,0.8), float radius = 0.1f);

            virtual void drawRay(const Ray& ray, const glm::vec3& color = glm::vec3(0.8,0.8,0.8), float diameter = 0.1f);

        public:

            SketchRenderer();
            virtual ~SketchRenderer();


    };


} // undicht

#endif // SKETCH_RENDERER_H
