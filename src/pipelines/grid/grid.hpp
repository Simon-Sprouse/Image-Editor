#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"
#include "../../variants/math/sequence_variants.hpp"

#include <vector>
using std::vector;

namespace grid { 

using image::Image, image::Color, image::Point;
using shapes::Rect, shapes::Axis_Table;


struct Parameters { 
    variant_fn::SequenceCommon seq_x_common;
    variant_fn::SequenceCommon seq_y_common;
    int thickness;
};

struct Cache { 
    Image original;
    Image canvas;
    Axis_Table ax;
};



class Grid { 

    public: 
        
        Grid(Parameters p) : params(p) {};

        void init(Cache& cache);
        void run(Cache& cache);

        // void setParameters(Parameters p); todo: what happens here? 
        // void clearData();
        


    private: 
        Parameters params;

        void drawGridLines(Image& canvas, const Axis_Table& ax);


};

}