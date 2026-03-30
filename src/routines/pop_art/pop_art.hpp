#pragma once

#include "../../data/image/image.hpp"

namespace pop_art { 

using image::Image, image::Color, image::Point;


struct Parameters { 
    int num_splits;
};

class PopArt { 
    public: 
        PopArt(const Parameters& p) : params(p) {};

        void loadExistingImage(const Image& img);

        Image getCanvas();

        void run();
        void runSlow();

    private: 
        Parameters params;
        Image original;
        Image gray;
        Image canvas;
        Image bin_map;
};

}