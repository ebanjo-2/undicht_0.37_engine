#ifndef SKETCH_RENDERER_H
#define SKETCH_RENDERER_H

#include <3D/renderer_3d.h>


#include <3D/math/ray.h>
#include <3D/math/plane.h>
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

            graphics::VertexBuffer m_var_mesh; // used to draw triangles, no fixed vertex positions

            graphics::Uniform m_color_uniform;

            Orientation3D m_draw_orientation; // to calculate the orientation of the models to draw

        public:
            // changing the way things are drawn

            /// @return this
            SketchRenderer* setDrawColor(const glm::vec3& color);

        public:
            // functions to draw simple geometry

            /// @return this
            virtual SketchRenderer* drawSphere(const glm::vec3& position, float radius = 0.1f);

            /// @return this
            virtual SketchRenderer* drawRay(const Ray& ray, float diameter = 0.1f);

            /// @return this
            virtual SketchRenderer* drawPlane(const Plane& plane, float diameter = 1000.0f);

            /// @return this
            virtual SketchRenderer* drawTriangle(const glm::vec3& pos_1, const glm::vec3& pos_2, const glm::vec3& pos_3);

        public:

            SketchRenderer();
            virtual ~SketchRenderer();


    };


} // undicht

#endif // SKETCH_RENDERER_H
