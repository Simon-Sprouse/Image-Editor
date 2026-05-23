#pragma once

#include "../../data/image/image.hpp"

using namespace image;

namespace transform::resize { 

    // nearest neighbor sampling - TODO more elegant sampling
    Size resizeImage(Image<RGB>& src, Image<RGB>& dest, int w, int h);
    Size resizeImage(Image<RGB>& src, Image<RGB>& dest, Size size);
    Size resizeImage(Image<RGB>& src, Image<RGB>& dest, double ratio);

}