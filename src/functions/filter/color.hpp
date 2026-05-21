#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

#include <vector>


using namespace image;

using shapes::Rect;

namespace filter::color { 

    RGB avgColor(const Image<RGB>& image, const Rect& rect);
    void toGrayscale(const Image<RGB>& src, Image<GRAY>& dest);

    // TODO: This is a BANDAID!!! finish committing to GRAY px type
    void toGrayscale(const Image<RGB>& src, Image<RGB>& dest);

}