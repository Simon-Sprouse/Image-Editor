#include "grid.hpp"


namespace grid { 


void Grid::loadExistingImage(const Image& image) { 
    original = image.clone();



    canvas = original.clone();
}

Image Grid::getCanvas() { 
    return canvas.clone();
}


}