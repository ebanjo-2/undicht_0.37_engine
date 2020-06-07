#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <graphics/texture.h>

namespace undicht {

    class ModelLoader {
        /** a class with common functions used to build both 2D and 3D models */
        public:
            // building vertices

            /** some file formats may store the attributes in a different order (i.e. pos, uv, normal or pos, normal, uv)
            * and with them the attribute indices. since undicht uses always the same order (pos, uv, normal), the indices may have to be rearranged
            * @param attribute_indices: the indices as they come from the file, @param new_order: the way they have to be rearranged to form the default order */
            virtual void rearrangeAttribIndices(const std::vector<int>& attrib_indices, std::vector<int> new_order, std::vector<int>& loadTo);

            /** takes an attribute (size determined by vertex_layout, can be UND_FLOAT, UND_VEC3F, ...) from each attribute_data list,
            * which attribute is determined by the attribute index, to build the vertices */
            virtual void buildVertices(std::vector<std::vector<float>>& attribute_data, const std::vector<int>& attribute_indices, const core::BufferLayout& vertex_layout, std::vector<float>& loadTo);

        public:
            // building indices

            /** removes double vertices by adding indices referencing the first version of that vertex to the loadTo_indices vector*/
            virtual void buildIndices(const std::vector<float>& vertices, const core::BufferLayout& vertex_layout, std::vector<float>& loadTo_vertices, std::vector<int>& loadTo_indices);


        public:
            // loading other assets

            /** easier way to load an Image File to a texture */
            virtual void loadTexture(graphics::Texture& texture, const std::string& file_name);

        public:


            ModelLoader();
            virtual ~ModelLoader();

    };


} // undicht

#endif // MODEL_LOADER_H
