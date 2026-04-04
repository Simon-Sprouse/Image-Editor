#include "grid.hpp"

#include "../../utils/graphics/line.hpp"
#include "../../utils/math/sequence.hpp"
#include "../../utils/filter/color.hpp"

#include <vector>
#include <iostream>

using std::cout, std::endl;
using std::vector;



namespace grid { 


void Grid::loadExistingImage(const Image& image) { 
    original = image.clone();



    canvas = original.clone();
}

Image Grid::getCanvas() { 
    return canvas.clone();
}

void Grid::run() { 




    vector<int> cols = math::sequence::uniformSamplesBounds(0, original.getWidth() - 1, params.cols);

    for (int i = 0; i < params.cols; i++) { 

        int current_col = cols[i];
        int next_col = cols[i+1];


        Point tl_corner = Point(current_col, 0);
        int dx = next_col - current_col - 1; // diff between index columns not including next column
        int dy = original.getHeight();
        Color avg_color = filter::color::avgColor(original, tl_corner, dx, dy);

        // todo move to graphics library
        for (int x = 0; x < dx; x++) { 
            for (int y = 0; y < dy; y++) { 
                canvas.setPixel(current_col + x, y, avg_color);
            }
        }

    }

    for (int col : cols) { 
        draw::line::drawCol(canvas, col, Color(255), 5);
    }
    

}


}