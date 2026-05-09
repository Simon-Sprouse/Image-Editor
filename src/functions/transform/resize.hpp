#pragma once

#include "../../data/image/image.hpp"

using namespace image;

namespace transform::resize { 

    // nearest neighbor sampling - TODO more elegant sampling
    Size resizeImage(Image<RGBA>& src, Image<RGBA>& dest, int w, int h);
    Size resizeImage(Image<RGBA>& src, Image<RGBA>& dest, Size size);
    Size resizeImage(Image<RGBA>& src, Image<RGBA>& dest, double ratio);

}