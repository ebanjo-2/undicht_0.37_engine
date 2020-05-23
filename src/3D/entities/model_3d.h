#ifndef MODEL_3D_H
#define MODEL_3D_H

#include <graphics/textured_mesh.h>
#include <3D/math/orientation_3d.h>

namespace undicht {


    class Model3D : public TexturedMesh, public Orientation3D {
        /** a class giving a textured mesh a 3D orientation*/
        public:

            std::vector<Model3D> m_child_models;

        public:

            /** @return a model that has an orientation relative to this model */
            Model3D& addChildModel();


            Model3D();
            virtual ~Model3D();

    };

} // undicht

#endif // MODEL_3D_H
