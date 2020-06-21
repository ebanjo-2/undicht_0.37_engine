#include "collada_file.h"

#include <core/event_logger.h>
#include <core/string_tools.h>

namespace undicht {

    const std::vector<std::string> primitive_types{"polylist", "triangles", "polygons", "lines", "trifans", "tristrips", "linestrips"};

    using namespace core;
    using namespace graphics;

    ColladaFile::ColladaFile() {
        //ctor
    }

    ColladaFile::ColladaFile(const std::string& file_name) {

        open(file_name);
    }

    ColladaFile::~ColladaFile() {
        //dtor
    }



    void ColladaFile::loadModel(Model3D& loadTo) {
        /** if the loaded model contains submodels,
        * they should be placed into the models m_child_models vector */

        // all materials stored in the file
        std::vector<XmlElement*> materials = getAllElements({"COLLADA", "library_materials", "material"});
        std::vector<Texture> material_textures;

        for(XmlElement* material : materials) {
            material_textures.emplace_back(Texture());
            loadMaterialTextures(material, material_textures.back());
        }

        // all geometries stored in the file
        std::vector<XmlElement*> geometries = getAllElements({"COLLADA", "library_geometries", "geometry"});


        for(XmlElement* e : geometries) {

            loadGeometry(*e, loadTo.addChildModel());

            // finding the material to the model
            XmlElement* mesh = e->getElement({"mesh"});
            std::string material_id;

            for(const std::string& primitive_type : primitive_types) {

                XmlElement* primitive = mesh->getElement({primitive_type});

                if(primitive) {
                    material_id = primitive->getAttribute("material")->m_value;
                    break;
                }
            }

            for(int i = 0; i < materials.size(); i++) {
                if(!materials.at(i)->getAttribute("id")->m_value.compare(material_id)) {
                    // found the right material
                    loadTo.m_child_models.back().getTexture() = material_textures.at(i);
                    break;
                }
            }

        }

    }

    ///////////////////////////// functions to bring more structure to the loading process ///////////////////////////


    void ColladaFile::loadGeometry(XmlElement& geometry, Model3D& loadTo) {

        // getting vertex data
        XmlElement* mesh = geometry.getElement({"mesh"});
        if(!mesh) return;

        XmlElement* position_source = getMeshSource(mesh, "POSITION");
        XmlElement* uv_source = getMeshSource(mesh, "TEXCOORD");
        XmlElement* normal_source = getMeshSource(mesh, "NORMAL");

        std::vector<std::vector<float>> attribute_data;
        BufferLayout vertex_layout;

        if(position_source) {
            attribute_data.emplace_back(std::vector<float>());
            extractFloatArray(attribute_data.back(), position_source->getContent(), -1);
            vertex_layout.m_types.push_back(UND_VEC3F);
        }

        if(uv_source) {
            attribute_data.emplace_back(std::vector<float>());
            extractFloatArray(attribute_data.back(), uv_source->getContent(), -1);
            vertex_layout.m_types.push_back(UND_VEC2F);
        }

        if(normal_source) {
            attribute_data.emplace_back(std::vector<float>());
            extractFloatArray(attribute_data.back(), normal_source->getContent(), -1);
            vertex_layout.m_types.push_back(UND_VEC3F);
        }

        // getting attribute index data
        XmlElement* index_source = 0;
        for(const std::string& primitive_type : primitive_types) {
            index_source = mesh->getElement({primitive_type, "p"});
            if(index_source) break;
        }

        if(!index_source) return;

        std::vector<int> attrib_indices, rearranged_attr_indices;
        extractIntArray(attrib_indices, index_source->getContent(), -1);

        rearrangeAttribIndices(attrib_indices, {0,2,1}, rearranged_attr_indices);

        // building the vertices
        std::vector<float> vertices;
        buildVertices(attribute_data, rearranged_attr_indices, vertex_layout, vertices);

        loadTo.getMesh().setData(vertices);
        loadTo.getMesh().setLayout(vertex_layout);
    }


    XmlElement* ColladaFile::getMeshSource(XmlElement* mesh, const std::string& source_name) {
        /** @param source_name: POSITION, NORMAL or TEXCOORD
        * @return the element containing the actual data (float array) */

        if(!mesh) return 0;

        bool position_source = !source_name.compare("POSITION");

        XmlElement* input_semantic = 0;

        if(position_source) {

            input_semantic = mesh->getElement({"vertices", "input semantic=" + ('"' + source_name) + '"'});
        } else {

            for(const std::string& primitive_type : primitive_types) {

                input_semantic = mesh->getElement({primitive_type, "input semantic=" + ('"' + source_name) + '"'});

                if(input_semantic) break;
            }
        }

        if(!input_semantic) return 0;

        const XmlTagAttrib* source_attribute = input_semantic->getAttribute("source");
        if(!source_attribute) return 0;

        std::string source_id = source_attribute->m_value;
        source_id.erase(1,1); // they put a stupid # here

        return mesh->getElement({"source id=" + source_id, "float_array"});
    }

    //////////////////////////////// functions to load textures for a material ////////////////////////////////

    void ColladaFile::loadMaterialTextures(XmlElement* material, Texture& loadTo) {

        XmlElement* instance_effect = material->getElement({"instance_effect"});
        if(!instance_effect) return;

        const XmlTagAttrib* effect_url = instance_effect->getAttribute("url");
        if(!effect_url) return;

        std::string effect_id = effect_url->m_value;
        effect_id.erase(1, 1); // removing stupid #
        XmlElement* effect = getElement({"COLLADA", "library_effects", "effect id=" + effect_id});
        if(!effect) return;

        XmlElement* diffuse_texture = effect->getElement({"profile_COMMON", "technique", "phong", "diffuse", "texture"});
        if(!diffuse_texture) return;

        const XmlTagAttrib* sampler_name = diffuse_texture->getAttribute("texture");
        if(!sampler_name) return;

        XmlElement* sampler_2D_source = effect->getElement({"profile_COMMON", "newparam sid=" + sampler_name->m_value, "sampler2D", "source"});
        if(!sampler_2D_source) return;

        XmlElement* image_name = effect->getElement({"profile_COMMON", "newparam sid=" + ('"' + sampler_2D_source->getContent()) + '"', "surface", "init_from"});
        if(!image_name) return;

        XmlElement* image_file_name = getElement({"COLLADA", "library_images", "image id=" + ('"' + image_name->getContent()) + '"', "init_from"});
        if(!image_file_name) return;

        loadTexture(loadTo, getFilePath(getFileName()) + image_file_name->getContent());

    }



} // undicht
