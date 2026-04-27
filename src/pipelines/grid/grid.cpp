#include "grid.hpp"

#include "../../functions/graphics/line.hpp"
#include "../../functions/graphics/polygon.hpp"
#include "../../functions/math/sequence.hpp"
#include "../../functions/math/geometry.hpp"
#include "../../functions/filter/color.hpp"

#include <vector>
#include <iostream>

using std::cout, std::endl;
using std::vector;



namespace grid { 






void Grid::init(Cache& cache) { 
    cache.canvas = cache.original.clone();
    cache.ax.x_table = math::sequence::sequenceSelector(params.seq_x);
    cache.ax.y_table = math::sequence::sequenceSelector(params.seq_y);
}



void Grid::run(Cache& cache) { 
    drawGridLines(cache.canvas, cache.ax);
}



void Grid::drawGridLines(Image& canvas, const Axis_Table& ax) { 

    // todo edge case where last column / row index is off screen
    for (int x : ax.x_table) { 
        draw::line::drawCol(canvas, x, Color(0), params.thickness);
    }

    for (int y : ax.y_table) { 
        draw::line::drawRow(canvas, y, Color(0), params.thickness);
    }
    
}


}