#include "master_renderer_3d.h"

#include <core/string_tools.h>


namespace undicht {

    using namespace core;

    const std::string DEFAULT_3D_CONFIG = getFilePath(UND_CODE_SRC_FILE) + "/default_renderers.und";


    MasterRenderer3D::MasterRenderer3D() {
        //ctor
    }

    MasterRenderer3D::~MasterRenderer3D() {
        //dtor
    }


    void MasterRenderer3D::initialize() {
        /** initialize using the default config */

        initialize(DEFAULT_3D_CONFIG);

    }

    void MasterRenderer3D::initialize(const std::string& config) {
        /** initialize with the given config
        * a MasterRenderer3D config may be linked in the engine config,
        * in which case the MasterRenderer3D will be automatically initialized with it */

    }

    void MasterRenderer3D::terminate() {


    }


} // undicht
