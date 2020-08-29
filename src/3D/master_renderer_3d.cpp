#include "master_renderer_3d.h"

#include <core/string_tools.h>
#include <core/event_logger.h>


namespace undicht {

    using namespace core;

    const std::string DEFAULT_3D_CONFIG = getFilePath(UND_CODE_SRC_FILE) + "default_renderers.und";

    window::GraphicsContext* MasterRenderer3D::s_context = 0;
    window::Window* MasterRenderer3D::s_window = 0;
    graphics::FrameBuffer* MasterRenderer3D::s_scene_framebuffer = 0;
    Camera3D* MasterRenderer3D::s_scene_camera = 0;

    // Renderers
    ForwardRenderer* MasterRenderer3D::s_forward_renderer = 0;



    bool MasterRenderer3D::s_update_viewport = true;


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
        initialize(config_reader, core::getFilePath(config));

    }

    void MasterRenderer3D::initialize(XmlElement& config, const std::string& file_path) {

        // creating the renderer objects
        s_forward_renderer = new ForwardRenderer;


        s_forward_renderer->loadSettings(config, "SimpleForward", file_path);
    }

    void MasterRenderer3D::terminate() {

        delete s_forward_renderer;

    }

    void MasterRenderer3D::setContext(window::GraphicsContext* context, window::Window* win, bool update_size) {
        /** setting the window the renderer should draw to
        * @param update_size: if true, the renderers output viewport will always be
        * the size of the window, even if it is resized */

        s_context = context;
        s_window = win;
        s_update_viewport = update_size;

    }


    //////////////////////////////////////////// managing the scene ////////////////////////////////////

    void MasterRenderer3D::getViewportSize(int& width, int& height) {

        int offset_x, offset_y;
        graphics::Renderer::getViewport(width, height, offset_x, offset_y);

    }


    void MasterRenderer3D::setSceneFramebuffer(graphics::FrameBuffer* fbo) {
        /** the framebuffer the scene gets drawn to
        * @param : 0 will set the output fbo to be the default framebuffer
        * which becomes visible after endFrame() gets called*/

        s_scene_framebuffer = fbo;
    }

    void MasterRenderer3D::setSceneCamera(const Camera3D& cam) {
        /** the camera which "captures" the current scene */

        s_scene_camera = (Camera3D*)&cam;
    }


    void MasterRenderer3D::newFrame() {

        if(!s_forward_renderer || !s_context || !s_window) {
            EventLogger::storeNote(Note(UND_ERROR, "MasterRenderer3D:ERROR: not initialized or no context/window set", UND_CODE_ORIGIN));
            return;
        }

        if(s_update_viewport) {
            // updating the viewport to be the size of the window
            int width, height;
            s_window->getSize(width, height);
            graphics::Renderer::setViewport(width, height);

        }

        // clearing all the framebuffers
        s_forward_renderer->clearFramebuffer(); // default and visible framebuffer

        // loading the camera to all renderers
        if(s_scene_camera) {

            s_forward_renderer->loadCamera(*s_scene_camera);

        }

    }

    void MasterRenderer3D::endFrame() {

        if(!s_forward_renderer || !s_context || !s_window) {
            return;
        }

        // displaying the content of the default framebuffer
        s_context->swapBuffers();

    }

} // undicht
