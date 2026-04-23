#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"
#include <vector>

using namespace image;
using namespace shapes;
using namespace std;

namespace pixelate { 


    struct Parameters { 
        vector<Rect> rectangles;
    };



    class Pixelate { 
        public: 

            Pixelate(Parameters p) : params_(p) {};

            void run();
            void init(const Image& image); // todo standardize and consolidate init() style logic in all routines
            Image getCanvas();
        private: 
            Parameters params_;

            Image original;
            Image canvas;

    };

}