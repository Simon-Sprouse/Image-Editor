#pragma once

// todo: languages should have better include syntax

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"
#include "../../data/image/color_map.hpp"

using namespace image;
using shapes::Rect;

namespace draw::polygon { 



    void drawRect(Image<RGB>& image, const Rect& rect, const RGB& color);

    void drawCmapCol(Image<RGB>& canvas, Rect rect, const Color_Map& cmap);
    void drawCmapRow(Image<RGB>& canvas, Rect rect, const Color_Map& cmap);
    



}