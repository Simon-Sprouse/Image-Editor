#include "pop_art.hpp"

namespace pop_art {



void PopArt::loadExistingImage(const Image& img) { 
    original = img.clone();
}

Image PopArt::getCanvas() { 
    return canvas.clone();
}


void PopArt::run() { 
    canvas = original.clone();
}



}