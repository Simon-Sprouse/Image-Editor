#pragma once

#include "Image.hpp"



#include <string>

using std::string;
using image::Image;

// TODO make this part of image namespace
namespace image::io {

    Image fromEncodedBuffer(const uint8_t* data, size_t size);
    Image loadImageFileSystem(const string& path);
    void saveImageFileSystem(const Image& img, const string& save_path);

}