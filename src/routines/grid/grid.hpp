#pragma once

#include "../../data/image/image.hpp"

namespace grid { 

using image::Image;

struct Parameters { 
    int rows;
    int cols;
};

class Grid { 

    public: 
        
        Grid() {};
        Grid(Parameters p) : params(p) {};

        void loadExistingImage(const Image& image);
        Image getCanvas();
        


    private: 
        Parameters params;

        Image original;
        Image canvas;

};

}