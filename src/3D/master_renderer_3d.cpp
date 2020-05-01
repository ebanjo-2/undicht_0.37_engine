#include "master_renderer_3d.h"

#include <core/string_tools.h>


namespace undicht {

    using namespace core;

    const std::string DEFAULT_3D_CONFIG = getFilePath(UND_CODE_SRC_FILE) + "/default_renderers.und";

    Renderer3D* MasterRenderer3D::s_forward_renderer;


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

        XmlFile config_reader(config);
        initialize(config_reader);

    }

    void MasterRenderer3D::initialize(XmlElement& config) {

        // creating the renderer objects
        s_forward_renderer = new Renderer3D;


        s_forward_renderer->loadSettings(config, "SimpleForward");
    }

    void MasterRenderer3D::terminate() {

        delete s_forward_renderer;

    }


} // undicht
