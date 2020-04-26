#include "engine.h"
#include <core/core.h>
#include <core/string_tools.h>

#include <window/window_lib.h>
#include <graphics/graphics_lib.h>
#include <audio/audio_lib.h>
#include <file/file_lib.h>

#include <engine/file_loading/xml/xml_file.h>



namespace undicht {

    using namespace core;
    using namespace window;
    using namespace graphics;
    using namespace audio;
    using namespace file;

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
        FileLib::initialize();

    }


    void Engine::initialize(const std::string& window, const std::string& video, const std::string& audio, const std::string& file) {
        /// initializes the engine with these libraries

        Core::setLibraryPaths(window, video, audio, file);

        initialize();

    }


    void Engine::initialize(const std::string& engine_config, const std::string& file_library) {
        /**  initializes the engine with the libraries from the engine_config file
        * @param file_library: if no file_library is given, the default library will be used to read the config */


        if(file_library.compare("")) {
            // the provided file library is going to be used
            Core::setLibraryPaths("", "", "", file_library);

        }


        // initializing only the file library
        Core::initialize(false, false, false, true);
        FileLib::initialize();

        // loading the other library file names from the config
        XmlFile m_config_reader(engine_config);
        m_config_reader.printRecursive();



#ifdef UND_UNIX
        XmlElement* core_libs = m_config_reader.getElement({"engine", "core_libraries", "UND_UNIX"});
#endif // UND_UNIX

#ifdef UND_WINDOWS
        XmlElement* core_libs = m_config_reader.getElement({"engine", "core_libraries", "UND_WINDOWS"});
#endif // UND_WINDOWS


        std::string window_lib = core_libs->getElement({"window_lib"})->getContent();
        std::string graphics_lib = core_libs->getElement({"graphics_lib"})->getContent();
        std::string audio_lib = core_libs->getElement({"audio_lib"})->getContent();
        std::string file_lib = core_libs->getElement({"file_lib"})->getContent();

        // initializing the core with the libraries from the config file

        std::string file_path = core::getFilePath(engine_config);

        Core::setLibraryPaths(file_path + window_lib, file_path + graphics_lib, file_path + audio_lib, file_path + file_lib);

        initialize();
    }


    void Engine::terminate() {
        /// to be called when the engine is no longer used

        FileLib::terminate();
        AudioLib::terminate();
        GraphicsLib::terminate();

        delete s_main_context;
        delete s_main_window;

        WindowLib::terminate();

        Core::terminate();

    }


} // undicht
