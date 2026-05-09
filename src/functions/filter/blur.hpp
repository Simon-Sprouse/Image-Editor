#pragma once 

#include "../../data/image/image.hpp"

using namespace image;


namespace filter::blur { 
    void gaussianBlur(Image<RGBA>& src, Image<RGBA>& dest, Size kernel_size, double blur_sigma);
    void gaussianBlur(Image<RGBA>& src, Image<RGBA>& dest, int kernel_size, double blur_sigma);
}