#ifndef MASTER_RENDERER_3D_H
#define MASTER_RENDERER_3D_H

#include <string>

#include <engine/file_loading/xml/xml_file.h>

#include <3D/renderer_3d.h>
#include <window/window.h>
#include <window/graphics_context.h>

#include <3D/entities/camera_3d.h>
#include <3D/entities/model_3d.h>
#include <3D/renderers/forward_renderer.h>


namespace undicht {

    class MasterRenderer3D {
            /** a class that has control over the 3D scene */

        private:

            friend ForwardRenderer;

            static window::GraphicsContext* s_context;
            static window::Window* s_window;

            static graphics::FrameBuffer* s_scene_framebuffer;
            static Camera3D* s_scene_camera;

            static bool s_update_viewport; // always update the viewport size to the size of the window

        public:
            // Renderers

            static ForwardRenderer* s_forward_renderer;

        public:

            /** initialize using the default config */
            static void initialize();

            /** initialize with the given config
            * a MasterRenderer3D config may be linked in the engine config,
            * in which case the MasterRenderer3D will be automatically initialized with it */
            static void initialize(const std::string& config);

            static void initialize(XmlElement& config, const std::string& file_path);

            static void terminate();

            /** setting the context the renderer should draw to
            * @param update_size: if true, the renderers output viewport will always be
            * the size of the window the context belongs to, even if it is resized */
            static void setContext(window::GraphicsContext* context, window::Window* win, bool update_size = true);

        public:
            // managing the scene

            static void getViewportSize(int& width, int& height);

            /** the framebuffer the scene gets drawn to
            * @param : 0 will set the output fbo to be the default framebuffer
            * which becomes visible after endFrame() gets called*/
            static void setSceneFramebuffer(graphics::FrameBuffer* fbo);

            /** the camera which "captures" the current scene */
            static void setSceneCamera(const Camera3D& cam);

            static void newFrame();

            static void endFrame();


        public:

            MasterRenderer3D();
            virtual ~MasterRenderer3D();

    };

} // undicht

#endif // MASTER_RENDERER_3D_H
