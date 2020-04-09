#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <window/graphics_context.h>
#include <window/window.h>

namespace undicht {


    class Engine {
        public:

            static window::GraphicsContext* s_main_context;
            static window::Window* s_main_window;

            /// initializes the engine with the default libraries
            static void initialize();

            /// initializes the engine with these libraries
            static void initialize(const std::string& window, const std::string& video, const std::string& audio, const std::string& file);

            /**  initializes the engine with the libraries from the engine_config file
            * @param file_library: if no file_library is given, the default library will be used to read the config */
            static void initialize(const std::string& engine_config, const std::string& file_library = "");

            /// to be called when the engine is no longer used
            static void terminate();


            Engine();
            virtual ~Engine();


    };

} // undicht

#endif // ENGINE_H
