#ifndef COLLADA_FILE_H
#define COLLADA_FILE_H

#include <3D/file_loading/model_loader_3d.h>
#include <engine/file_loading/xml/xml_file.h>


namespace undicht {

    class ColladaFile : public ModelLoader3D, public XmlFile {

        private:
            // functions to bring more structure to the loading process

            virtual void loadGeometry(XmlElement& geometry, std::vector<float>& vertices, core::BufferLayout& vertex_layout);

            virtual void loadGeometry(XmlElement& geometry, Model3D& loadTo);


            /** @param source_name: POSITION, NORMAL or TEXCOORD
            * @return the element containing the actual data (float array) (0 if the mesh does not have a source with that name) */
            virtual XmlElement* getMeshSource(XmlElement* mesh, const std::string& source_name);

            // functions to load textures for a material

            virtual void loadMaterialTextures(XmlElement* material, graphics::Texture& loadTo);

        public:

            /** loads the vertex data of all the meshes of the model + their layouts */
            virtual void loadVertexData(std::vector<std::vector<float>>& vertices, std::vector<core::BufferLayout>& vertex_layouts);

            /** if the loaded model contains submodels,
            * they should be placed into the models m_child_models vector */
            virtual void loadModel(Model3D& loadTo);

            ColladaFile();
            ColladaFile(const std::string& file_name);
            virtual ~ColladaFile();

    };

} // undicht

#endif // COLLADA_FILE_H
