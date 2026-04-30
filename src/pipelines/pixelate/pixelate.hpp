#pragma once

#include "../../data/image/image.hpp"
#include "../../data/shapes/shapes.hpp"
#include "../../variants/math/sequence_variants.hpp"

#include <vector>

using namespace image;
using namespace shapes;
using namespace std;

namespace pixelate { 


    struct Parameters { 
        variant_fn::SequenceCommon seq_x_common;
        variant_fn::SequenceCommon seq_y_common;
    };

    struct Cache { 
        Image original;
        Image canvas;
        Axis_Table ax;
        vector<Rect> rect_table;
    };


    class Pixelate { 
        public: 

            Pixelate(Parameters p) : params(p) {};

            // for now init expects cold start, later we will do selective updates
            void init(Cache& cache); // todo standardize and consolidate init() style logic in all pipelines
            void run(Cache& cache);
            
            
        private: 

            void drawRectAreas(const Image& original, Image& canvas, const vector<Rect>& rect_table);

            Parameters params;

    };

}