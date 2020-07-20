#include "textured_mesh.h"

namespace undicht {

    TexturedMesh::TexturedMesh() {
        //ctor
        //m_texture.setName("mesh_texture");
    }

    TexturedMesh::~TexturedMesh() {
        //dtor
    }


    void TexturedMesh::setMesh(const graphics::VertexBuffer& mesh) {

        m_mesh = mesh;
    }


    graphics::VertexBuffer& TexturedMesh::getMesh() {

        return m_mesh;
    }

    void TexturedMesh::setTexture(const graphics::Texture& texture) {

        m_texture = texture;

    }

    graphics::Texture& TexturedMesh::getTexture() {

        return m_texture;
    }

} // undicht
