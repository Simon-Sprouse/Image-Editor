#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"
#include "../../functions/math/sequence.hpp"

#include <vector>
using std::vector;

namespace grid { 

using image::Image, image::Color, image::Point;
using Seq = math::sequence::SequenceParams;
using shapes::Rect, shapes::Axis_Table;


struct Parameters { 
    Seq seq_x;
    Seq seq_y;
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