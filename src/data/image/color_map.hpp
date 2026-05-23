#pragma once 

#include "primitives.hpp"
#include "pixel.hpp"

// todo this namespace and also shapes need to have location re-thought
namespace image { 

    struct Color_Stop { 
        HSV color;
        float x_pos;
    };
    static_assert(sizeof(Color_Stop) == 8);







}