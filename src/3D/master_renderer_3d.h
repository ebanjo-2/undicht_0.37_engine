#ifndef MASTER_RENDERER_3D_H
#define MASTER_RENDERER_3D_H

#include <string>

namespace undicht {

    class MasterRenderer3D {
    /** a class that has control over the 3d renderers
    * and which can hold functions that use more then just one Renderer (i.e. deferred lighting) */
        public:

            /** initialize using the default config */
            void initialize();

            /** initialize with the given config
            * a MasterRenderer3D config may be linked in the engine config,
            * in which case the MasterRenderer3D will be automatically initialized with it */
            void initialize(const std::string& config);

            void terminate();

            MasterRenderer3D();
            virtual ~MasterRenderer3D();

    };

} // undicht

#endif // MASTER_RENDERER_3D_H
