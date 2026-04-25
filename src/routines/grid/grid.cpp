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

    int num_coords = (params.cols - 1) * (params.rows - 1);
    rect_coords.reserve(num_coords);
}

Image Grid::getCanvas() { 
    return canvas.clone();
}

void Grid::computeRectCoords() { 


    cols = math::sequence::uniformSamplesBounds(0, original.getWidth(), params.cols); // todo: should be name indexes
    rows = math::sequence::uniformSamplesBounds(0, original.getHeight(), params.rows);


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


    for (int i = 0; i < cols.size() - 1; i++) { 
        for (int j = 0; j < rows.size() - 1; j++) { 
            Rect coord = Rect{Point(cols[i], rows[j]), col_intervals[i], row_intervals[j]};
            rect_coords.push_back(coord);
        }
    }

}


void Grid::drawRectAreas() { 
    for (Rect rect : rect_coords) { 

        // todo overload with polygon struct
        Color avg_color = filter::color::avgColor(original, rect);

        draw::polygon::drawRect(canvas, rect.tl, rect.dx, rect.dy, avg_color);

    }
}

void Grid::drawGridLines() { 

    // todo edge case where last column / row index is off screen
    for (int col : cols) { 
        draw::line::drawCol(canvas, col, Color(0), params.thickness);
    }

    for (int row : rows) { 
        draw::line::drawRow(canvas, row, Color(0), params.thickness);
    }
    
}



void Grid::run() { 

    computeRectCoords();
    drawRectAreas();
    drawGridLines();


}

void Grid::setParameters(Parameters p) { 
    params = p;
}

void Grid::clearData() { 
    params = Parameters();

    rect_coords.clear();
    cols.clear();
    rows.clear();

    canvas = Image(original.size());
}


}