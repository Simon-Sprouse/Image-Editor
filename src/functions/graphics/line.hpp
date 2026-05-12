#pragma once

#include "../../data/image/image.hpp"


using namespace image;


namespace draw::line { 





    void drawCol(Image<RGBA>& image, int col_index, const RGBA& color, int thickness);
    void drawRow(Image<RGBA>& image, int row_index, const RGBA& color, int thickness);

}