#pragma once 

#include "../../data/image/image.hpp"

using namespace image;


namespace filter::blur { 
    void gaussianBlur(Image<RGB>& src, Image<RGB>& dest, Size kernel_size, double blur_sigma);
    void gaussianBlur(Image<RGB>& src, Image<RGB>& dest, int kernel_size, double blur_sigma);
}