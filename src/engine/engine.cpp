#include "engine.h"
#include <core/core.h>

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



/*#ifdef UND_UNIX
        XmlElement* core_libs = m_config_reader.m_root_XmlElement.findSubordinated("core_libraries")->findSubordinated("UND_UNIX");
#endif // UND_UNIX

#ifdef UND_WINDOWS
        XmlElement* core_libs = m_config_reader.m_root_XmlElement.findSubordinated("core_libraries")->findSubordinated("UND_WINDOWS");
#endif // UND_WINDOWS

        std::cout << m_config_reader.m_root_XmlElement << "\n";

        std::string window_lib = core_libs->findSubordinated("window_lib")->m_content;
        std::string graphics_lib = core_libs->findSubordinated("graphics_lib")->m_content;
        std::string audio_lib = core_libs->findSubordinated("audio_lib")->m_content;
        std::string file_lib = core_libs->findSubordinated("file_lib")->m_content;

        std::cout << "window lib: " << window_lib << "\n";

        // initializing the core with the libraries from the config file
        Core::setLibraryPaths(window_lib, graphics_lib, audio_lib, file_lib);*/

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
