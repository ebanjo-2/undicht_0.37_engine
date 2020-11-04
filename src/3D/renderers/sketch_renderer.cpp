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

        m_var_mesh.setLayout(BufferLayout({UND_VEC3F}));

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
        m_draw_orientation.setScale(glm::vec3(diameter, diameter, 1000.0f));

        loadModelOrientation(m_draw_orientation);
        submit(&m_cube_mesh);

        draw();

        return this;
    }


    SketchRenderer* SketchRenderer::drawPlane(const Plane& plane, float diameter) {

        prepare();

        // same math as for the ray
        float yaw_angle = plane.getNormal().z != 0.0f ? glm::atan(plane.getNormal().x / plane.getNormal().z) : 0.5 * 3.14159;
        float pitch_angle = glm::asin(plane.getNormal().y / glm::length(plane.getNormal()));

        m_draw_orientation.setAxesRotation({0,glm::degrees(pitch_angle), glm::degrees(yaw_angle)});
        m_draw_orientation.setPosition(plane.getPoint());
        m_draw_orientation.setScale(glm::vec3(diameter, diameter, 0.07f)); // the plane is less thick then a ray, to allow rays on a plane to be visible


        loadModelOrientation(m_draw_orientation);
        submit(&m_cube_mesh);

        draw();

        return this;
    }


    SketchRenderer* SketchRenderer::drawTriangle(const glm::vec3& pos_1, const glm::vec3& pos_2, const glm::vec3& pos_3) {

        prepare();

        std::vector<float> vertices = {pos_1.x, pos_1.y, pos_1.z, pos_2.x, pos_2.y, pos_2.z, pos_3.x, pos_3.y, pos_3.z};
        m_var_mesh.setData(vertices);

        m_draw_orientation.setAxesRotation({0, 0, 0});
        m_draw_orientation.setPosition(glm::vec3(0,0,0));
        m_draw_orientation.setScale(glm::vec3(1.0f, 1.0f, 1.0f));

        loadModelOrientation(m_draw_orientation);
        submit(&m_var_mesh);

        draw();

        return this;
    }


} // undicht
