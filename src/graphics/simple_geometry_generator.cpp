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
        std::vector<int> face_indices = {0,1,2, 0,2,3};

        for(int positive_direction = 0; positive_direction < 2; positive_direction++) {

            for(int axis = 0; axis < 3; axis++) {

                for(int vertex = 0; vertex < 6; vertex++) {

                    bool facing_x = !(bool)(axis - 0);
                    bool facing_y = !(bool)(axis - 1);
                    bool facing_z = !(bool)(axis - 2);

                    int index;
                    if(positive_direction)
                        index = face_indices[vertex];
                    if(!positive_direction)
                        index = face_indices[6 - vertex]; // switching the order of the positions

                    float x,y,z;

                    if(facing_x) {
                        x = -0.5f + positive_direction;
                        y = -0.5f + ((index == 1) || (index == 2) ? 0:1);
                        z = -0.5f + (index > 1 ? 0:1);
                    }

                    if(facing_y) {
                        x = -0.5f + (index > 1 ? 0:1);
                        y = -0.5f + positive_direction;
                        z = -0.5f + ((index == 1) || (index == 2) ? 0:1);
                    }

                    if(facing_z) {
                        x = -0.5f + ((index == 1) || (index == 2) ? 0:1);
                        y = -0.5f + (index > 1 ? 0:1);
                        z = -0.5f + positive_direction;
                    }

                    loadTo.insert(loadTo.end(), {x * size, y * size, z * size});

                }

            }

        }

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
