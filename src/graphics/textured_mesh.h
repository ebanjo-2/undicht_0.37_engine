#ifndef TEXTURED_MESH_H
#define TEXTURED_MESH_H

#include <graphics/texture.h>
#include <graphics/vertex_buffer.h>



namespace undicht {


    class TexturedMesh {
        /** a class combining a texture (possibly holding more then one 2D texture) and a mesh */
        // since this kind of class may be used within both a 3D and 2D context,
        // it was placed into the generic "graphics" folder of the engine

        public:

            graphics::VertexBuffer m_mesh;
            graphics::Texture m_texture;

        public:

            virtual void setMesh(const graphics::VertexBuffer& mesh);
            virtual graphics::VertexBuffer& getMesh();

            virtual void setTexture(const graphics::Texture& texture);
            virtual graphics::Texture& getTexture();

            TexturedMesh();
            virtual ~TexturedMesh();

    };

} // undicht

#endif // TEXTURED_MESH_H
