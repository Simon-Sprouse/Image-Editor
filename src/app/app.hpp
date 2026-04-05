#pragma once 

#include <string>
#include <iostream>
#include "../data/image/image.hpp"

using std::string;
using image::Image;

namespace app { 


    struct ImageResult { 
        Image image;
        string label;

        bool empty() const {return image.empty();}
    };

    void testIterators(string image_path, string save_dir);
    void mainLoop(string image_path, string save_dir);
}