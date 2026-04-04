#pragma once

#include "../../data/image/image.hpp"

namespace draw::polygon { 

    using image::Image, image::Point, image::Color;

    void drawRect(Image& image, const Point& tl_corner, int dx, int dy, const Color& color);



}