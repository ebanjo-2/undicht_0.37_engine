#include "engine.h"
#include <core/core.h>

#include <window/window_lib.h>
#include <graphics/graphics_lib.h>
#include <audio/audio_lib.h>



namespace undicht {

    using namespace core;
    using namespace window;
    using namespace graphics;
    using namespace audio;
    //using namespace file;

    window::GraphicsContext* Engine::s_main_context = 0;
    window::Window* Engine::s_main_window = 0;

    Engine::Engine() {
        //ctor
    }

    Engine::~Engine() {
        //dtor
    }


    void Engine::initialize() {
        /// initializes the engine with the default libraries

        Core::initialize();

        WindowLib::initialize();

        s_main_context = new GraphicsContext;
        s_main_window = new Window;
        s_main_window->open();
        s_main_context->createOnWindow(s_main_window);

        GraphicsLib::initialize(s_main_context);
        AudioLib::initialize();

    }


    void Engine::initialize(const std::string& window, const std::string& video, const std::string& audio, const std::string& file) {
        /// initializes the engine with these libraries

        Core::setLibraryPaths(window, video, audio, file);

        initialize();

    }


    void Engine::initialize(const std::string& engine_config, const std::string& file_library) {
        /**  initializes the engine with the libraries from the engine_config file
        * @param file_library: if no file_library is given, the default library will be used to read the config */
    }


    void Engine::terminate() {
        /// to be called when the engine is no longer used

        AudioLib::terminate();
        GraphicsLib::terminate();

        delete s_main_context;
        delete s_main_window;

        WindowLib::terminate();

        Core::terminate();

    }


} // undicht
