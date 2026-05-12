#pragma once

#include "image.hpp"

#include <opencv2/core.hpp>

#include <string>

using std::string;


// TODO make this part of image namespace
namespace image::io {

    Image<RGBA> fromEncodedBuffer(const uint8_t* data, size_t size);
    Image<RGBA> loadImageFileSystem(const string& path);
    void saveImageFileSystem(const Image<RGBA>& img, const string& save_path);
    cv::Mat imageToCvMat(const Image<RGBA>& source_image);

}