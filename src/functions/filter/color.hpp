#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

#include <vector>


using image::Image, image::RGBA, image::Point;
using shapes::Rect;

namespace filter::color { 

    RGBA avgColor(const Image& image, const Rect& rect);



    void toGrayscale(const Image& src, Image& dest);
}