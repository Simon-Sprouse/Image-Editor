#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"

#include <vector>
using std::vector;
using shapes::Rect;

namespace grid { 

using image::Image, image::Color, image::Point;

struct Parameters { 
    int rows;
    int cols;
    int thickness;
};



class Grid { 

    public: 
        
        Grid() {};
        Grid(Parameters p) : params(p) {};

        void loadExistingImage(const Image& image);

        void computeRectCoords();
        void drawRectAreas();
        void drawGridLines();
        void run();
        Image getCanvas();
        void setParameters(Parameters p);
        void clearData();
        


    private: 
        Parameters params;

        vector<Rect> rect_coords;
        vector<int> cols;
        vector<int> rows;


        Image original;
        Image canvas;

};

}