#include "line.hpp"

#include <vector>
#include <iostream>

using std::cout, std::endl;

using std::vector;

namespace { 




}

namespace draw::line { 

    void drawCol(Image& image, int col_index, const Color& color, int thickness) {

        int start_col = std::max(0, col_index - thickness/2);

        int linear_start = image.getLinearIndex(start_col, 0);
        int height = image.getHeight();
        int width = image.getWidth();
        int pointer;

        for (int i = 0; i < thickness; i++) { 
            pointer = linear_start + i;
            for (int y = 0; y < height; y++) { 
                image.setPixel(pointer, color);
                pointer += width;
            }
        }


    }



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