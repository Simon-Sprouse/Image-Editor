#pragma once

#include "../../data/image/image.hpp"

namespace draw::line { 

    using image::Image, image::Color;

    void drawColumn();
    void drawRow(Image& image, int row_index, const Color& color, int thickness);

}