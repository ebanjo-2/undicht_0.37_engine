#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <string>
#include <engine/file_loading/xml/xml_file.h>

#include <graphics/renderer.h>

namespace undicht {

    class MasterRenderer3D;

    class Renderer3D : protected graphics::Renderer {
        /** the base class to all 3D Renderers of the undicht engine */

        protected:

            friend MasterRenderer3D;

            graphics::Shader m_shader;

            bool m_enable_depth_test = false;
            bool m_cull_back_face = false;

        public:
            // general rendering settings

            void setShaderSource(const std::string& file_name);

            /** culling the backface of a triangle that has its vertices in an clockwise order*/
            void setCullBackface(bool enable = true);

            /** new pixels drawn onto the current framebuffer will be checked
            * if they are covered by other pixels with lower depth values */
            void enableDepthTest(bool enable = true);

        public:
            // to load the renderers setting from a .und config file

            /** loads the settings stored in the file for the renderer with the name
            * the renderer config should be stored at engine/Rendering/_3D/ */
            void loadSettings(XmlElement& config, const std::string& name, const std::string& file_path);

        public:
            // rendering functions

            /** to be called before the renderer is used
            * activates the settings saved to the renderer */
            void prepare();

        public:

            Renderer3D();
            virtual ~Renderer3D();



    };

} // undicht

#endif // RENDERER3D_H
