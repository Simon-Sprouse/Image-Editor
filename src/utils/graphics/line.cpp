#include "line.hpp"

// todo: logical circular dependency
#include "polygon.hpp"

#include "../../data/shapes/shapes.hpp"


#include <vector>
#include <iostream>

using std::cout, std::endl;

using std::vector;

using shapes::Rect;



namespace { 




}

namespace draw::line { 

    void drawCol(Image& image, int col_index, const Color& color, int thickness) {

    
        int start_col = std::max(0, col_index - thickness/2);
        int end_col = std::min(image.getWidth() - 1, start_col + thickness - 1);
        int bounded_dx = end_col - start_col + 1;
        Point tl(start_col, 0);
        draw::polygon::drawRect(image, Rect{tl, bounded_dx, image.getHeight()}, color);


    }



    void drawRow(Image& image, int row_index, const Color& color, int thickness) {

        int start_row = std::max(0, row_index - (thickness/2));
        int end_row = std::min(image.getHeight()-1, start_row + (thickness-1));
        int bounded_dy = end_row - start_row + 1;
        Point tl(0, start_row);
        draw::polygon::drawRect(image, Rect{tl, image.getWidth(), bounded_dy}, color);

    }

}