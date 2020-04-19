#ifndef XML_FILE_H
#define XML_FILE_H


#include <file/file.h>
#include "xml_element.h"


namespace undicht {


    class XmlFile : public file::File, public XmlElement {
        /** a class that can be used to read xml style files
        * after being opened, the XmlFile object resembles the root element of the file */
        private:

            /// reads and processes the next line of the file
            virtual void readNextLine();

        public:

            // loads the root element and all its sub elements
            virtual bool open(const std::string& file_name);

            XmlFile();
            XmlFile(const std::string& file_name);
            virtual ~XmlFile();


    };


} // undicht

#endif // XML_FILE_H
