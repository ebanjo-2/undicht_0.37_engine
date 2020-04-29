#include "engine_config.h"
#include <core/event_logger.h>

namespace undicht {

    using namespace core;


    EngineConfig::EngineConfig() {
        //ctor
    }

    EngineConfig::EngineConfig(const std::string& file_name) {

        open(file_name);

    }

    EngineConfig::~EngineConfig() {
        //dtor
    }

    void EngineConfig::getLibraries(std::string& window_lib, std::string& graphics_lib, std::string& audio_lib, std::string& file_lib) {
        /** extracts file names of the core libraries */

#ifdef UND_UNIX
        XmlElement* core_libs = getElement({"engine", "core_libraries", "UND_UNIX"});
#endif // UND_UNIX

#ifdef UND_WINDOWS
        XmlElement* core_libs = getElement({"engine", "core_libraries", "UND_WINDOWS"});
#endif // UND_WINDOWS

        if(!core_libs) {
            EventLogger::storeNote(Note(UND_ERROR, "ERROR: failed to read engine config: " + getName(), UND_CODE_ORIGIN));
        }

        std::string file_path = core::getFilePath(getFileName());

        window_lib = file_path + core_libs->getElement({"window_lib"})->getContent();
        graphics_lib = file_path + core_libs->getElement({"graphics_lib"})->getContent();
        audio_lib = file_path + core_libs->getElement({"audio_lib"})->getContent();
        file_lib = file_path + core_libs->getElement({"file_lib"})->getContent();

    }


} // undicht
