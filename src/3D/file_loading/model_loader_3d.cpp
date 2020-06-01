#include "model_loader_3d.h"
#include <graphics/file_loading/image_file.h>

namespace undicht {

    ModelLoader3D::ModelLoader3D() {
        //ctor
    }

    ModelLoader3D::~ModelLoader3D() {
        //dtor
    }


    void ModelLoader3D::rearrangeAttribIndices(const std::vector<int>& attrib_indices, std::vector<int> new_order, std::vector<int>& loadTo) {
        /** some file formats may store the attributes in a different order (i.e. pos, uv, normal or pos, normal, uv)
        * and with them the attribute indices. since undicht uses always the same order (pos, uv, normal), the indices may have to be rearranged
        * @param attribute_indices: the indices as they come from the file, @param new_order: the way they have to be rearranged to form the default order */

        int attributes_per_vertex = new_order.size();
        int vertex_count = attrib_indices.size() / attributes_per_vertex;

        for(int vertex_id = 0; vertex_id < vertex_count; vertex_id += 1) {
            // going through each vertex

            for(int attrib = 0; attrib < attributes_per_vertex; attrib++) {
                // going through each attribute index of the new indices list

                loadTo.push_back(attrib_indices.at(vertex_id * attributes_per_vertex + new_order.at(attrib)));
            }

        }

    }


    void ModelLoader3D::buildVertices(std::vector<std::vector<float>>& attribute_data, const std::vector<int>& attribute_indices, const core::BufferLayout& vertex_layout, std::vector<float>& loadTo) {
        /** takes an attribute (size determined by vertex_layout, can be UND_FLOAT, UND_VEC3F, ...) from each attribute_data list,
        * which attribute is determined by the attribute index, to build the vertices */

        int attributes_per_vertex = vertex_layout.m_types.size();
        int vertex_count = attribute_indices.size() / attributes_per_vertex;

        std::vector<int> attribute_sizes; // the number of floats of each attribute used in a vertex

        for(int attribute_type : vertex_layout.m_types) {

            attribute_sizes.push_back(core::getSizeOfType(attribute_type));
        }

        for(int vertex_id = 0; vertex_id < vertex_count; vertex_id += 1) {
            // going through each vertex

            for(int attrib = 0; attrib < attributes_per_vertex; attrib++) {
                // going through each attribute

                std::vector<float>& current_attrib_list = attribute_data.at(attrib);
                int index = attribute_indices.at(vertex_id * attributes_per_vertex + attrib);

                std::vector<float>::iterator data_begin = current_attrib_list.begin() + index * attribute_sizes.at(attrib);
                std::vector<float>::iterator data_end = data_begin + attribute_sizes.at(attrib) - 1;

                loadTo.insert(loadTo.end(), data_begin, data_end);
            }

        }

    }


    void ModelLoader3D::loadTexture(graphics::Texture& texture, const std::string& file_name) {
        /** easier way to load an Image File to a texture */

        ImageFile image(file_name);
        image.loadToTexture(texture);

    }

} // undicht
