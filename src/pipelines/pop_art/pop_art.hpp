#pragma once

#include "../../data/image/image.hpp"

namespace pop_art { 

using image::RGBA, image::Point;
using namespace image;



struct Parameters { 
    int num_splits;
};

class PopArt { 
    public: 
        PopArt(const Parameters& p) : params(p) {};

        void loadExistingImage(const Image<RGBA>& img);

        Image<RGBA> getCanvas();


        void findBins_();
        void run();
        void runPersistent();
        void runSlow();

    private: 
        Parameters params;
        Image<RGBA> original;
        Image<GRAY> gray;
        Image<RGBA> canvas;
        Image<RGBA> bin_map;
};

}