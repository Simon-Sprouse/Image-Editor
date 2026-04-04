#pragma once

#include "../../data/image/image.hpp"

#include <vector>


using image::Image, image::Color, image::Point;

namespace filter::color { 

    Color avgColor(const Image& image, const Point& tl_corner, int dx, int dy);



    void toGrayscale(const Image& src, Image& dest);
}