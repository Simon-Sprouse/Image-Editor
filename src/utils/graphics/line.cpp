#include "line.hpp"

#include <vector>
#include <iostream>

using std::cout, std::endl;

using std::vector;

namespace { 




}

namespace draw::line { 

    void drawColumn() {}



    void drawRow(Image& image, int row_index, const Color& color, int thickness) {

        // find row indicies to achieve thickness
        int start_row = std::max(0, row_index - (thickness/2));
        int end_row = std::min(image.getHeight()-1, start_row + (thickness-1));

        int linear_start;
        int width = image.getWidth();
        for (int row = start_row; row <= end_row; row++) { 
            linear_start = image.getLinearIndex(0, row);
            for (int x = 0; x < width; x++) { 
                image.setPixel(linear_start + x, color);
            }
        }

    }

}