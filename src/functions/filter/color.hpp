#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

#include <vector>


using namespace image;

using shapes::Rect;

namespace filter::color { 

    RGBA avgColor(const Image<RGBA>& image, const Rect& rect);
    void toGrayscale(const Image<RGBA>& src, Image<GRAY>& dest);

    // TODO: This is a BANDAID!!! finish committing to GRAY px type
    void toGrayscale(const Image<RGBA>& src, Image<RGBA>& dest);

}