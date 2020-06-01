#ifndef IMAGE_FILE_H
#define IMAGE_FILE_H

#include <graphics/texture.h>
#include <vector>


namespace undicht {


    class ImageFile {
        /** implemented using the stb image lib  */

        protected:

            std::string m_file_name;

        public:
            // loading the data from the image file

            void loadImageData(std::vector<char>& image_data, int& width, int& height, int& nr_channels);

            void loadToTexture(graphics::Texture& texture);

        public:

            virtual void open(const std::string& file_name);

            ImageFile();
            ImageFile(const std::string& file_name);
            virtual ~ImageFile();


    };


} // undict

#endif // IMAGE_FILE_H
