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

    enum class dimension { 
        x,
        y,
        z
    };

    struct Axis_Table { 
        dimension dim;
        vector<int> indexes;
    };



}