#include "grid.hpp"

#include "../../utils/graphics/line.hpp"
#include "../../utils/graphics/polygon.hpp"
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




    vector<int> cols = math::sequence::uniformSamplesBounds(0, original.getWidth(), params.cols);
    vector<int> rows = math::sequence::uniformSamplesBounds(0, original.getHeight(), params.rows);

    vector<int> col_intervals;
    col_intervals.reserve(params.cols - 1); // eg 10 seperation indexes means 9 interval spaces between

    for (int i = 0; i < params.cols; i++) { 
        int current_col = cols[i];
        int next_col = cols[i+1];

        int dx = next_col - current_col;
        col_intervals.push_back(dx);
    }

    // todo handle both interval and index calculation together (likely both elsewhere)
    vector<int> row_intervals;
    row_intervals.reserve(params.rows - 1);
    for (int i = 0; i < params.rows; i++) {
        int current_row = rows[i];
        int next_row = rows[i+1];

        int dy = next_row - current_row;
        row_intervals.push_back(dy);
    }


    // Todo: structs for polygon shapes? 
    struct Rect { 
        Point tl_corner;
        int dx;
        int dy;
    };

    vector<Rect> coords;
    coords.reserve((cols.size() - 1) * (rows.size() - 1));


    for (int i = 0; i < cols.size() - 1; i++) { 
        for (int j = 0; j < rows.size() - 1; j++) { 
            Rect coord = Rect{Point(cols[i], rows[j]), col_intervals[i], row_intervals[j]};
            coords.push_back(coord);
        }
    }




    for (Rect coord : coords) { 

        // todo overload with polygon struct
        Color avg_color = filter::color::avgColor(original, coord.tl_corner, coord.dx, coord.dy);

        // todo move to graphics library
        draw::polygon::drawRect(canvas, coord.tl_corner, coord.dx, coord.dy, avg_color);

    }

    int thickness = 1;

    // todo edge case where last column / row index is off screen
    for (int col : cols) { 
        draw::line::drawCol(canvas, col, Color(0), thickness);
    }

    for (int row : rows) { 
        draw::line::drawRow(canvas, row, Color(0), thickness);
    }
    

}


}