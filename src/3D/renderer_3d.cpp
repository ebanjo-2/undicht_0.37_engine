#include "renderer_3d.h"
#include <core/event_logger.h>
#include <core/types.h>


#include <glm/glm/gtc/type_ptr.hpp>



namespace undicht {

    using namespace core;
    using namespace file;
    using namespace graphics;

    Renderer3D::Renderer3D() {
        //ctor
    }

    Renderer3D::~Renderer3D() {
        //dtor
    }

    /////////////////////////////////////////// general rendering settings ///////////////////////////////////////////////////////////

    void Renderer3D::setShaderSource(const std::string& file_name) {

        File shader_source;
        if(!shader_source.open(file_name)) {

            EventLogger::storeNote(Note(UND_ERROR, "Renderer3D: ERROR: failed to open shader src: " + file_name, UND_CODE_ORIGIN));
            return;
        }

        std::string src_buffer;
        m_shader.loadSource(shader_source.getAll(src_buffer));

    }


    void Renderer3D::setCullBackface(bool enable) {
        /** culling the backface of a triangle that has its vertices in an clockwise order*/

        m_cull_back_face = enable;

    }


    void Renderer3D::enableDepthTest(bool enable) {
        /** new pixels drawn onto the current framebuffer will be checked
        * if they are covered by other pixels with lower depth values */

        m_enable_depth_test = enable;

    }

    void Renderer3D::setFrameBuffer(graphics::FrameBuffer* framebuffer) {
        /** sets the FrameBuffer that the Renderer should draw to
        * @param : passing 0 will make the Renderer draw to the visible framebuffer */

        m_frame_buffer = framebuffer;
    }

    //////////////////////////////// to load the renderers setting from a .und config file /////////////////////////////////////////////

    void Renderer3D::loadSettings(XmlElement& config, const std::string& name, const std::string& file_path) {
        /** loads the settings stored in the file for the renderer with the name
        * the renderer config should be stored at engine/Rendering/_3D/ */

        XmlElement* settings = config.getElement({"engine", "Rendering", "_3D", name});

        if(!settings || !settings->hasChildElements({"init_from", "enable_depth_test", "cull_back_face"})) {
            // should work even if settings is a nullptr
            EventLogger::storeNote(Note(UND_ERROR, "failed to load render config: " + name, UND_CODE_ORIGIN));
            return;
        }

        setShaderSource(file_path + settings->getElement({"init_from"})->getContent());
        enableDepthTest(!settings->getElement({"enable_depth_test"})->getContent().compare("true"));
        setCullBackface(!settings->getElement({"cull_back_face"})->getContent().compare("true"));

        // uniform names (may also be stored in the file in the future, but for now im using preset names)
        m_view_uniform.setName("view");
        m_proj_uniform.setName("proj");
        m_model_uniform.setName("model");
        m_model_scale.setName("scale");

    }


    //////////////////////////////// rendering functions ////////////////////////////////

    void Renderer3D::prepare() {
        /** to be called before the renderer is used
        * activates the settings saved to the renderer */

        graphics::Renderer::enableBackFaceCulling(m_cull_back_face);
        graphics::Renderer::enableDepthTest(m_enable_depth_test);

        submit(m_frame_buffer);
        submit(&m_shader);

    }

                //////////////////////////////// functions that only should be used by the MasterRenderer or child classes ////////////////////////////////

    void Renderer3D::loadCamera(Camera3D& cam) {

        m_view_uniform.setData(glm::value_ptr(cam.getViewMatrix()), UND_MAT4F);
        m_proj_uniform.setData(glm::value_ptr(cam.getCameraProjectionMatrix()), UND_MAT4F);

        m_shader.loadUniform(m_view_uniform);
        m_shader.loadUniform(m_proj_uniform);
    }

    void Renderer3D::loadModelOrientation(Orientation3D& orientation) {

        m_model_uniform.setData(glm::value_ptr(orientation.getTransfMat()), UND_MAT4F);

        m_shader.loadUniform(m_model_uniform);
    }

    void Renderer3D::loadModelScale(const glm::vec3& scale) {

        m_model_scale.setData(glm::value_ptr(scale), UND_VEC3F);

        m_shader.loadUniform(m_model_scale);
    }



} // undicht
