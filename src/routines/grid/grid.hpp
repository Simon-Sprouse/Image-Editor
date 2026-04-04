#pragma once

#include "../../data/image/image.hpp"

namespace grid { 

using image::Image, image::Color, image::Point;

struct Parameters { 
    int rows;
    int cols;
};

class Grid { 

    public: 
        
        Grid() {};
        Grid(Parameters p) : params(p) {};

        void loadExistingImage(const Image& image);
        void run();
        Image getCanvas();
        


    private: 
        Parameters params;

        Image original;
        Image canvas;

};

}