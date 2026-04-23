#include "pixelate.hpp"

using namespace image;

namespace pixelate { 

    void Pixelate::init(const Image& image) {
        original = image.clone();
        canvas = image.clone();
    }
    

    Image Pixelate::getCanvas() { 
        return canvas.clone();
    }

    void Pixelate::run() { 

    }
}