#include "sketch_renderer.h"

#include <graphics/simple_geometry_generator.h>
#include <core/types.h>
#include <3D/master_renderer_3d.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include <3D/math/math_tools.h>



namespace undicht {

    using namespace core;

    SketchRenderer::SketchRenderer() {

        SimpleGeometryGenerator g;

        std::vector<float> vertices;

        g.genCube(vertices);

        m_cube_mesh.setData(vertices);
        m_cube_mesh.setLayout(BufferLayout({UND_VEC3F}));

        vertices.clear();

        g.genSphere(vertices);

        m_sphere_mesh.setData(vertices);
        m_sphere_mesh.setLayout(BufferLayout({UND_VEC3F}));

        m_color_uniform.setName("color");
    }

    SketchRenderer::~SketchRenderer() {
        //dtor
    }

    ////////////////////////////////////// changing the way things are drawn ////////////////////////////////////

    SketchRenderer* SketchRenderer::setDrawColor(const glm::vec3& color) {

        m_color_uniform.setData(glm::value_ptr(color), UND_VEC3F);
        m_shader.loadUniform(m_color_uniform);

        return this;
    }


    //////////////////////////////////// functions to draw simple geometry ////////////////////////////////////


    SketchRenderer* SketchRenderer::drawSphere(const glm::vec3& position, float radius) {

        prepare();

        m_draw_orientation.setAxesRotation({0,0,0});
        m_draw_orientation.setScale(glm::vec3(radius));
        m_draw_orientation.setPosition(position);

        loadModelOrientation(m_draw_orientation);

        submit(&m_sphere_mesh);

        draw();

        return this;
    }

    SketchRenderer* SketchRenderer::drawRay(const Ray& ray, float diameter) {

        prepare();

        float yaw_angle = ray.getDir().z != 0.0f ? glm::atan(ray.getDir().x / ray.getDir().z) : 0.5 * 3.14159;
        float pitch_angle = glm::asin(ray.getDir().y / glm::length(ray.getDir()));


        m_draw_orientation.setAxesRotation({0,glm::degrees(pitch_angle), glm::degrees(yaw_angle)});
        m_draw_orientation.setPosition(ray.getPoint());
        m_draw_orientation.setScale(glm::vec3(0.1f, 0.1f, 1000.0f));

        loadModelOrientation(m_draw_orientation);
        submit(&m_cube_mesh);

        draw();

        return this;
    }



} // undicht
