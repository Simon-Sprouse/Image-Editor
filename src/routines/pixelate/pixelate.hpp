#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

#include <vector>

using namespace image;
using namespace shapes;
using namespace std;

namespace pixelate { 


    struct Parameters { 
        Axis_Table x_idx;
        Axis_Table y_idx;
    };



    class Pixelate { 
        public: 

            Pixelate(Parameters p) : params_(p) {};

            void run();
            void drawRectAreas();
            void init(const Image& image); // todo standardize and consolidate init() style logic in all routines
            Image getCanvas();
        private: 
            Parameters params_;

            vector<Rect> rect_table_;

            Image original;
            Image canvas;

    };

}