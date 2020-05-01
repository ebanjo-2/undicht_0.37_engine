#include "renderer_3d.h"
#include <core/event_logger.h>


namespace undicht {

    using namespace core;

    Renderer3D::Renderer3D() {
        //ctor
    }

    Renderer3D::~Renderer3D() {
        //dtor
    }

    /////////////////////////////////////////// general rendering settings ///////////////////////////////////////////////////////////

    void Renderer3D::setShaderSource(const std::string& file_name) {


    }


    void Renderer3D::setCullBackface(bool enable) {
        /** culling the backface of a triangle that has its vertices in an clockwise order*/

    }


    void Renderer3D::enableDepthTest(bool enable) {
        /** new pixels drawn onto the current framebuffer will be checked
        * if they are covered by other pixels with lower depth values */

    }

    //////////////////////////////// to load the renderers setting from a .und config file /////////////////////////////////////////////

    void Renderer3D::loadSettings(XmlElement& config, const std::string& name) {
        /** loads the settings stored in the file for the renderer with the name
        * the renderer config should be stored at engine/Rendering/_3D/ */

        XmlElement* settings = config.getElement({"engine", "Rendering", "_3D", name});

        if(!settings || !settings->hasChildElements({"init_from", "enable_depth_test", "cull_back_face"})) {
            // should work even if settings is a nullptr
            EventLogger::storeNote(Note(UND_ERROR, "failed to load render config: " + name, UND_CODE_ORIGIN));
            return;
        }

        setShaderSource(settings->getElement({"init_from"})->getContent());
        enableDepthTest(!settings->getElement({"enable_depth_test"})->getContent().compare("true"));
        setCullBackface(!settings->getElement({"cull_back_face"})->getContent().compare("true"));


    }

} // undicht
