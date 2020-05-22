#include "textured_mesh.h"

namespace undicht {

    TexturedMesh::TexturedMesh() {
        //ctor
    }

    TexturedMesh::~TexturedMesh() {
        //dtor
    }


    graphics::VertexBuffer& TexturedMesh::getMesh() {

        return m_mesh;
    }

    graphics::Texture& TexturedMesh::getTexture() {

        return m_texture;
    }

} // undicht
