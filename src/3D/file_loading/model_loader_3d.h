#ifndef MODEL_LOADER_3D_H
#define MODEL_LOADER_3D_H

#include <vector>
#include <3D/entities/model_3d.h>
#include <graphics/model_loader.h>


namespace undicht {


    class ModelLoader3D {
        /** base class to all classes that load 3D models,
        * providing them with some commonly used functions */

        public:
            // model loading api

            /** if the loaded model contains submodels,
            * they should be placed into the models m_child_models vector */
            virtual void loadModel(const Model3D& loadTo);


            ModelLoader3D();
            virtual ~ModelLoader3D();

    };


} // undicht

#endif // MODEL_LOADER_3D_H
