#pragma once

#include "../image/image.hpp"
#include <vector>

using namespace std;
using namespace image;

namespace shapes {
    
    struct Rect { 
        Point tl;
        int dx;
        int dy;
    };

    // todo overload operators on rect like comp and equals



    struct Axis_Table { 
        vector<int> x_table;
        vector<int> y_table;
    };



}