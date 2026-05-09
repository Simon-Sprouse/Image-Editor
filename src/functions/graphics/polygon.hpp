#pragma once

// todo: languages should have better include syntax

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

using namespace image;
using shapes::Rect;

namespace draw::polygon { 



    void drawRect(Image<RGBA>& image, const Rect& rect, const RGBA& color);



}