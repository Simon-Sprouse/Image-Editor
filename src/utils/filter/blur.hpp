#pragma once 

#include "../../data/image/image.hpp"

using image::Image, image::Size;

namespace filter::blur { 
    void gaussianBlur(Image& src, Image& dest, Size kernel_size, double blur_sigma);
    void gaussianBlur(Image& src, Image& dest, int kernel_size, double blur_sigma);
}