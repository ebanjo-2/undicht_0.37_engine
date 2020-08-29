#include "image_file.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <core/event_logger.h>
#include <core/buffer_layout.h>
#include <core/types.h>


namespace undicht {

    using namespace core;

    ImageFile::ImageFile() {
        //ctor
    }

    ImageFile::ImageFile(const std::string& file_name) {

        open(file_name);
    }


    ImageFile::~ImageFile() {
        //dtor
    }

    void ImageFile::open(const std::string& file_name) {

        m_file_name = file_name;

    }


    //////////////////////////////// loading the data from the image file ////////////////////////////////

    void ImageFile::loadImageData(std::vector<char>& image_data, int& width, int& height, int& nr_channels) {

        stbi_set_flip_vertically_on_load(true);


        //loading the image data
        unsigned char* data = stbi_load(m_file_name.data(), &width, &height, &nr_channels, 0);

        if(data) { //testing whether the image could be loaded or not

            //loading the data to the texture
            image_data.insert(image_data.begin(), data, data + width * height * nr_channels * sizeof(char));

        } else {

            EventLogger::storeNote(Note(UND_ERROR,  "CORE:TEXTURE:ERROR: failed to read image: " + m_file_name, UND_CODE_ORIGIN));

        }

        stbi_image_free(data);
    }

    void ImageFile::loadToTexture(graphics::Texture& texture) {

        std::vector<char> data_buffer;
        int width, height, nr_channels;
        BufferLayout layout;

        loadImageData(data_buffer, width, height, nr_channels);

        for(int i = 0; i < nr_channels; i++) {

            layout.m_types.push_back(UND_UNSIGNED_CHAR);
        }

        texture.setPixelFormat(layout);
        texture.setSize(width, height);
        texture.setData(data_buffer.data(), data_buffer.size() * sizeof(char));

    }


} // undicht
