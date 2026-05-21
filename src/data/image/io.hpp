#pragma once

#include "image.hpp"

#include <opencv2/core.hpp>

#include <string>

using std::string;


// TODO make this part of image namespace
namespace image::io {

    Image<RGB> fromEncodedBuffer(const uint8_t* data, size_t size);
    Image<RGB> loadImageFileSystem(const string& path);
    void saveImageFileSystem(const Image<RGB>& img, const string& save_path);
    cv::Mat imageToCvMat(const Image<RGB>& source_image);
    cv::Mat imageToCvMat(const Image<HSV>& source_image);

}