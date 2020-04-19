#include "xml_file.h"


namespace undicht {

    XmlFile::XmlFile() {
        //ctor
    }

    XmlFile::XmlFile(const std::string& file_name) {
        //ctor
        open(file_name);
    }

    XmlFile::~XmlFile() {
        //dtor
    }

    bool XmlFile::open(const std::string& file_name) {

        if(!(file::File*)(this)->open(file_name)) {
            // failed to open
            return false;
        }




    }

} // undicht
