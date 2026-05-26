#pragma once 

#include "primitives.hpp"
#include "pixel.hpp"

#include <array>
#include <vector>
#include <cstring> // for std::memcpy
#include <iostream>
#include <cmath>

using namespace std;

// todo this namespace and also shapes need to have location re-thought
namespace image { 

    // todo template this
    struct Color_Stop { 
        HSV color;
        float x_pos; // 0-1

        Color_Stop(HSV _color, float _x_pos) : color(_color), x_pos(_x_pos) {}
    };
    static_assert(sizeof(Color_Stop) == 8);

    class Color_Map { 
    public: 

        // constructors
        // todo Color_Map(vector<HSV> colors) // for equal spacing
        // todo consider constructors that don't pass LUT size
        Color_Map(vector<Color_Stop> _stops, int _N);

        HSV at(int i) const { 
            return lut[i]; 
        }
        HSV frac(float f) const { 
            return lut[static_cast<int>(N * f)]; 
        }
        HSV frac(int i, int total) const { 
            // todo: input validation i <= total
            float track_pos = (static_cast<float>(i) / (total-1)) * N;
            return lut[static_cast<int>(track_pos)];
        }


        vector<Color_Stop> stops;
        vector<HSV> lut;
        int N;

    };

    

    vector<HSV> lerpMulti(HSV color_0, HSV color_1, int num_steps);
    int getIdxFromXPos(float x_pos, int N); // helper for lerpMulti
    
    

}