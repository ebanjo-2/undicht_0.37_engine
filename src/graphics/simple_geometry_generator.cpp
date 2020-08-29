#include "simple_geometry_generator.h"
#include <glm/glm/glm.hpp>

// i quite enjoyed coming up with the algorithm to generate the meshes of the geometric forms
// i am sure there are better ways to doing this though
// 07.06.2020


namespace undicht {

    using namespace core;

    SimpleGeometryGenerator::SimpleGeometryGenerator() {
        //ctor
    }

    SimpleGeometryGenerator::~SimpleGeometryGenerator() {
        //dtor
    }


    //////////////////////////////////////////////////////// 3D ////////////////////////////////////////////////////////

    void SimpleGeometryGenerator::genCube(std::vector<float>& loadTo, float size) {

        std::vector<float> vertex_positions = {
            -0.5,-0.5, -0.5,
            0.5, -0.5, -0.5,
            0.5, -0.5,  0.5,
            -0.5,-0.5,  0.5, // bottom

            -0.5, 0.5, -0.5,
            0.5,  0.5, -0.5,
            0.5,  0.5, 0.5,
            -0.5, 0.5, 0.5 // top
        };

        // scaling the vertex positions
        for(float& f : vertex_positions) {
            f *= size;
        }

        const std::vector<int> face_indices = {
            0, 1, 3, 1, 2, 3, // bottom
            4, 7, 5, 5, 7, 6, // top
            0, 3, 4, 3, 7, 4, // left
            2, 5, 6, 2, 1, 5, // right
            3, 2, 6, 3, 6, 7, // front
            0, 4, 1, 1, 4, 5  // back
        };

        buildVertices({vertex_positions}, face_indices, BufferLayout({UND_VEC3F}), loadTo);

    }

    void SimpleGeometryGenerator::genSphere(std::vector<float>& loadTo, int resolution, float radius) {
        /** @param resolution: number of vertices per circle around the sphere  */

        // generating a cylinder for each vertical ring around the sphere
        for(float ring = 0; ring < resolution; ring++) {

            genCylinder(loadTo, resolution, false, 1.0f, 1.0f / resolution); // making the cylinders with a radius and length of 1

            float x_offset = -0.5f + (ring + 0.5f) / resolution;

            // moving the cylinder to the right spot
            for(int vertex = 0; vertex < resolution * 6; vertex++ ) {

                // accessing the x value of each vertex position
                int x_index = ring * resolution * 6 * 3 + vertex * 3;

                loadTo.at(x_index) += x_offset;
                loadTo.at(x_index) *= 2.0f;

                // making the sphere
                float circle_radius = glm::sqrt(1 - glm::pow(loadTo.at(x_index), 2.0f));
                loadTo.at(x_index + 1) *= circle_radius;
                loadTo.at(x_index + 2) *= circle_radius;

                // resizing the sphere
                loadTo.at(x_index) *= radius;
                loadTo.at(x_index + 1) *= radius;
                loadTo.at(x_index + 2) *= radius;

            }

        }

    }

    void SimpleGeometryGenerator::genCylinder(std::vector<float>& loadTo, int resolution, bool close_ends, float radius, float length) {

        std::vector<int> face_indices = {0,1,2, 0,2,3};

        std::vector<float> end_vertices;

        for(float step = 0; step < resolution; step += 1.0f) {

            for(int vertex = 0; vertex < 6; vertex++) {

                int index = face_indices[vertex];

                float x,y,z;

                if(index == 0) {

                    x = -0.5f;
                    y = glm::cos(step / resolution * glm::radians(360.0f));
                    z = glm::sin(step / resolution * glm::radians(360.0f));

                } else if (index == 1) {

                    x = -0.5f;
                    y = glm::cos((step + 1.0f) / resolution * glm::radians(360.0f));
                    z = glm::sin((step + 1.0f)  / resolution * glm::radians(360.0f));

                } else if (index == 2) {

                    x = 0.5f;
                    y = glm::cos((step + 1.0f)  / resolution * glm::radians(360.0f));
                    z = glm::sin((step + 1.0f)  / resolution * glm::radians(360.0f));

                } else if (index == 3) {

                    x = 0.5f;
                    y = glm::cos(step / resolution * glm::radians(360.0f));
                    z = glm::sin(step / resolution * glm::radians(360.0f));

                }

                loadTo.insert(loadTo.end(), {x * length, y * radius, z * radius});

                if(close_ends && ((vertex <= 1) || (vertex >= 4))) {
                    // closing the ends

                    end_vertices.insert(end_vertices.end(), {x * length, y * radius, z * radius});
                }

                if(close_ends && ((vertex == 0) || (vertex == 4))) {
                    // closing the ends pt. 2 (vertex in the middle)

                    end_vertices.insert(end_vertices.end(), {x * length, 0, 0});
                }

            }

        }

        if(close_ends) {

            loadTo.insert(loadTo.end(), end_vertices.begin(), end_vertices.end());
        }


    }

} // undicht
