#pragma once

#include "../../data/image/image.hpp"

namespace draw::line { 

    using image::Image, image::Color;

    void drawCol(Image& image, int col_index, const Color& color, int thickness);
    void drawRow(Image& image, int row_index, const Color& color, int thickness);

}