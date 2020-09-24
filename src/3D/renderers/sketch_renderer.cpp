#include "sketch_renderer.h"

#include <graphics/simple_geometry_generator.h>
#include <core/types.h>
#include <3D/master_renderer_3d.h>
#include <glm/glm/gtc/type_ptr.hpp>



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

    void SketchRenderer::setDrawColor(const glm::vec3& color) {

        m_color_uniform.setData(glm::value_ptr(color), UND_VEC3F);
        m_shader.loadUniform(m_color_uniform);

    }


    //////////////////////////////////// functions to draw simple geometry ////////////////////////////////////


    void SketchRenderer::drawSphere(const glm::vec3& position, const glm::vec3& color, float radius) {

        m_draw_orientation.setScale(glm::vec3(radius));
        m_draw_orientation.setPosition(position);

        loadModelOrientation(m_draw_orientation);

        submit(&m_sphere_mesh);

        draw();
    }

    void SketchRenderer::drawRay(const Ray& ray, const glm::vec3& color, float diameter) {

        /*m_cube_model.setScale(glm::vec3(diameter, diameter, 1000.0));
        m_cube_model.setPosition(ray.getPoint());

        // calculating the rotation (works only if the ray is not parallel to the x or y axis)
        // 1. rotation around y axis

        float angle_y = 0;

        if(ray.getDir().z != 0) {
            angle_y = glm::degrees(glm::atan(ray.getDir().x/ray.getDir().z));
        } else {
            angle_y = 90;
        }

        glm::quat rot = glm::angleAxis(angle_y, glm::vec3(0,1,0));


        // adding pitch
        glm::vec3 pitch_axis = glm::cross(ray.getDir(), glm::vec3(0,1,0));

        if(!glm::length(pitch_axis)) {
            pitch_axis = glm::vec3(1,0,0);
        } else {
            pitch_axis = glm::normalize(pitch_axis);
        }

        float pitch_angle = glm::degrees(glm::asin(ray.getDir().y / glm::length(ray.getDir())));

        rot = glm::rotate(rot, pitch_angle, pitch_axis);

        m_cube_model.setRotation(rot);

        // changing the rays color to match its direction
        unsigned char rgba[4] = {color.x * 255, color.y * 255, color.z * 255, 1};

        m_cube_model.getTexture().setPixelFormat(BufferLayout({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR}));
        m_cube_model.getTexture().setSize(1,1);
        m_cube_model.getTexture().setData((char*)rgba,4);


        MasterRenderer3D::s_forward_renderer->drawModel(m_cube_model);*/
    }


} // undicht
