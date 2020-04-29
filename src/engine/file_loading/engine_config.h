#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

#include <engine/file_loading/xml/xml_file.h>

namespace undicht {


    class EngineConfig : public XmlFile {
        /** a class for used to initialize the undicht engine
        * with configurations stored in .und files */
        public:

            /** extracts file names of the core libraries */
            virtual void getLibraries(std::string& window_lib, std::string& graphics_lib, std::string& audio_lib, std::string& file_lib);

            EngineConfig();
            EngineConfig(const std::string& file_name);
            virtual ~EngineConfig();

    };

} // undicht

#endif // ENGINE_CONFIG_H
