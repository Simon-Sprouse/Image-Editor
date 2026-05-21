#pragma once

#include "../../data/image/image.hpp"


using namespace image;


namespace draw::line { 





    void drawCol(Image<RGB>& image, int col_index, const RGB& color, int thickness);
    void drawRow(Image<RGB>& image, int row_index, const RGB& color, int thickness);

}