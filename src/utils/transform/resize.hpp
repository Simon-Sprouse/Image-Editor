#pragma once

#include "../../data/image/image.hpp"

using image::Size, image::Image;

namespace resize { 

    // nearest neighbor sampling - TODO more elegant sampling
    Size resizeImage(Image& src, Image& dest, int w, int h);
    Size resizeImage(Image& src, Image& dest, Size size);
    Size resizeImage(Image& src, Image& dest, double ratio);

}