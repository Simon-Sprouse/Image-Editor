#include "grid.hpp"

#include "../../utils/graphics/line.hpp"
#include "../../utils/math/sequence.hpp"

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


    vector<int> rows = math::sequence::uniformSamples(0, original.getHeight() - 1, params.rows - 1);

    for (int row : rows) { 
        draw::line::drawRow(canvas, row, Color(0), 5);
    }

}


}