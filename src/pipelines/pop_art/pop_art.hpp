#pragma once

#include "../../data/image/image.hpp"

namespace pop_art { 

using image::RGB, image::Point;
using namespace image;



struct Parameters { 
    int num_splits;
};

class PopArt { 
    public: 
        PopArt(const Parameters& p) : params(p) {};

        void loadExistingImage(const Image<RGB>& img);

        Image<RGB> getCanvas();


        void findBins_();
        void run();
        void runPersistent();
        void runSlow();

    private: 
        Parameters params;
        Image<RGB> original;
        Image<GRAY> gray;
        Image<RGB> canvas;
        Image<RGB> bin_map;
};

}