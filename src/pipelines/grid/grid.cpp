#include "grid.hpp"

#include "../../functions/graphics/line.hpp"
#include "../../functions/graphics/polygon.hpp"
#include "../../functions/math/geometry.hpp"
#include "../../functions/filter/color.hpp"

#include <vector>
#include <iostream>

using std::cout, std::endl;
using std::vector;

using namespace image;


namespace grid { 






void Grid::init(Cache& cache) { 
    cache.canvas = cache.original.clone();
    cache.ax.x_table = variant_fn::sequenceFn(params.seq_x_common);
    cache.ax.y_table = variant_fn::sequenceFn(params.seq_y_common);
}



void Grid::run(Cache& cache) { 
    drawGridLines(cache.canvas, cache.ax);
}



void Grid::drawGridLines(Image<RGBA>& canvas, const Axis_Table& ax) { 

    // todo edge case where last column / row index is off screen
    for (int x : ax.x_table) { 
        draw::line::drawCol(canvas, x, RGBA(0), params.thickness);
    }

    for (int y : ax.y_table) { 
        draw::line::drawRow(canvas, y, RGBA(0), params.thickness);
    }
    
}


}