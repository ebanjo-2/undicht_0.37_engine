#include "model_loader_3d.h"
#include <graphics/file_loading/image_file.h>

namespace undicht {

    ModelLoader3D::ModelLoader3D() {
        //ctor
    }

    ModelLoader3D::~ModelLoader3D() {
        //dtor
    }





    //////////////////////////////////////////////////// model loading api ////////////////////////////////////////////////////


    void ModelLoader3D::loadModel(Model3D& loadTo) {
        /** if the loaded model contains submodels,
        * they should be placed into the models m_child_models vector */


    }

    void ModelLoader3D::loadVertexData(std::vector<std::vector<float>>& vertices, std::vector<core::BufferLayout>& layouts) {
        /** loads the vertex data of all the meshes of the model + their layouts */

    }

    void ModelLoader3D::loadHitbox(PolygonHitbox& loadTo) {

        std::vector<std::vector<float>> vertices;
        std::vector<core::BufferLayout> layouts;

        loadVertexData(vertices, layouts);

        if(vertices.size() != layouts.size()) {
            // something is not right in the loadVertexData function of the implementing class
            return;
        }

        for(int i = 0; i < vertices.size(); i++) {
            // adding a new simple polygon hitbox
            float vertex_size = layouts.at(i).getTotalSize() / sizeof(float); // number of floats per vertex
            float polygon_size = vertex_size * 3;
            SimplePolygonHitbox& hitb = loadTo.addHitbox();

            for(int polygon = 0; polygon < vertices.at(i).size() / polygon_size; polygon++) {
                // going through each polygon of the mesh

                std::vector<glm::vec3> positions;

                for(int vertex = 0; vertex < 3; vertex++) {
                    // going through each vertex of the polygon
                    int first_float_id = polygon * polygon_size + vertex * vertex_size;

                    positions.push_back(glm::vec3(vertices.at(i).at(first_float_id + 0), vertices.at(i).at(first_float_id + 1), vertices.at(i).at(first_float_id + 2)));
                }

                hitb.addPolygon(HitboxPolygon(positions));

            }

        }

    }



} // undicht
