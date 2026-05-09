#pragma once

#include "../../data/image/image.hpp"

namespace draw::line { 

    using image::Image, image::RGBA, image::Point;

    void drawCol(Image& image, int col_index, const RGBA& color, int thickness);
    void drawRow(Image& image, int row_index, const RGBA& color, int thickness);

}