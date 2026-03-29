#pragma once

#include "../../data/image/image.hpp"

namespace pop_art { 

using image::Image;


struct Parameters { 
    int num_splits = 2;
};

class PopArt { 
    public: 
        PopArt(const Parameters& p) : params(p) {};

        void loadExistingImage(const Image& img);

        Image getCanvas();

        void run();

    private: 
        Parameters params;
        Image original;
        Image canvas;
};

}