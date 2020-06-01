#ifndef MODEL_LOADER_3D_H
#define MODEL_LOADER_3D_H

#include <vector>
#include <graphics/textured_mesh.h>


namespace undicht {


    class ModelLoader3D {
        /** base class to all classes that load 3D models,
        * providing them with some commonly used functions */
        public:

            /** some file formats may store the attributes in a different order (i.e. pos, uv, normal or pos, normal, uv)
            * and with them the attribute indices. since undicht uses always the same order (pos, uv, normal), the indices may have to be rearranged
            * @param attribute_indices: the indices as they come from the file, @param new_order: the way they have to be rearranged to form the default order */
            virtual void rearrangeAttribIndices(const std::vector<int>& attrib_indices, std::vector<int> new_order, std::vector<int>& loadTo);

            /** takes an attribute (size determined by vertex_layout, can be UND_FLOAT, UND_VEC3F, ...) from each attribute_data list,
            * which attribute is determined by the attribute index, to build the vertices */
            virtual void buildVertices(std::vector<std::vector<float>>& attribute_data, const std::vector<int>& attribute_indices, const core::BufferLayout& vertex_layout, std::vector<float>& loadTo);

            /** easier way to load an Image File to a texture */
            virtual void loadTexture(graphics::Texture& texture, const std::string& file_name);


            ModelLoader3D();
            virtual ~ModelLoader3D();

    };


} // undicht

#endif // MODEL_LOADER_3D_H
