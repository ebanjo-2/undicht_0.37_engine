#include "collada_file.h"

#include <core/event_logger.h>
#include <core/string_tools.h>

namespace undicht {

    using namespace core;

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

        // all geometries stored in the file
        std::vector<XmlElement*> geometries = getAllElements({"COLLADA", "library_geometries", "geometry"});

        for(XmlElement* e : geometries) {

            loadGeometry(*e, loadTo.addChildModel());

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
        XmlElement* index_source = mesh->getElement({"triangles", "p"});
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

        std::string semantic_parent = (!source_name.compare("POSITION") ? "vertices" : "triangles");

        XmlElement* input_semantic = mesh->getElement({semantic_parent, "input semantic=" + ('"' + source_name) + '"'});
        if(!input_semantic) return 0;

        const XmlTagAttrib* source_attribute = input_semantic->getAttribute("source");
        if(!source_attribute) return 0;

        std::string source_id = source_attribute->m_value;
        source_id.erase(1,1); // they put a stupid # here

        return mesh->getElement({"source id=" + source_id, "float_array"});
    }



} // undicht
