#pragma once

// todo: languages should have better include syntax

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

namespace draw::polygon { 

    using image::Image, image::Point, image::Color;
    using shapes::Rect;

    void drawRect(Image& image, const Rect& rect, const Color& color);



}