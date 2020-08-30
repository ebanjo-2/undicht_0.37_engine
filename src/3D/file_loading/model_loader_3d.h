#ifndef MODEL_LOADER_3D_H
#define MODEL_LOADER_3D_H

#include <vector>
#include <3D/entities/model_3d.h>
#include <3D/physics/hitboxes/polygon_hitbox.h>
#include <graphics/model_loader.h>



namespace undicht {


    class ModelLoader3D : public ModelLoader {
        /** base class to all classes that load 3D models,
        * providing them with some commonly used functions */

        public:
            // model loading api

            /** loads the vertex data of all the meshes of the model + their layouts */
            virtual void loadVertexData(std::vector<std::vector<float>>& vertices, std::vector<core::BufferLayout>& layouts);

            /** if the loaded model contains submodels,
            * they should be placed into the models m_child_models vector */
            virtual void loadModel(Model3D& loadTo);

            virtual void loadHitbox(PolygonHitbox& loadTo);


            ModelLoader3D();
            virtual ~ModelLoader3D();

    };


} // undicht

#endif // MODEL_LOADER_3D_H
