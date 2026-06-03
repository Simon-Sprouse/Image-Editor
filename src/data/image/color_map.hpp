#pragma once 

#include "primitives.hpp"
#include "pixel.hpp"
#include "image.hpp"

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
        Color_Map();
        Color_Map(HSV color_1, HSV color_2);
        Color_Map(const vector<HSV>& colors);
        // todo parallel arrays constructor
        Color_Map(const vector<Color_Stop>& stops);

        // methods
        RGB frac(float pos) const;
        RGB step(int index, int size) const; // designed to work cleanly in a loop size is max + 1

        // visualization
        Image<RGB> display(Size size);

        // data
        vector<Color_Stop> stops;
        // bool isDiscrete
        // int numDiscreteSteps

    };

    

    HSV lerp(HSV color_0, HSV color_1, float position);
    // todo rename
    vector<HSV> lerpMulti(HSV color_0, HSV color_1, int num_stops);
    int getIdxFromXPos(float x_pos, int N); // helper for lerpMulti
    
    

   
    // CONSTANTS todo: should these live here? 
    inline const vector<Color_Stop> VIRIDIS_STOPS = {
        Color_Stop(HSV(1230, 252, 84), 0.0f),
		Color_Stop(HSV(1126, 170, 120), 0.111f),
		Color_Stop(HSV(986, 140, 137), 0.222f),
		Color_Stop(HSV(872, 167, 142), 0.333f),
		Color_Stop(HSV(797, 187, 142), 0.444f),
		Color_Stop(HSV(725, 205, 158), 0.556f),
		Color_Stop(HSV(645, 181, 183), 0.667f),
		Color_Stop(HSV(464, 146, 206), 0.778f),
		Color_Stop(HSV(314, 206, 222), 0.889f),
		Color_Stop(HSV(229, 218, 253), 1.0f)

    };

    // todo this breaks sometimes? 
    // inline const Color_Map VIRIDIS = Color_Map(VIRIDIS_STOPS, 1000);



    inline const vector<Color_Stop> COSMOS_STOPS = {
        Color_Stop(HSV(1200, 255, 50), 0.0f),
        Color_Stop(HSV(150, 150, 255), 1.0f)
    };

    // inline const Color_Map COSMOS = Color_Map(COSMOS_STOPS, 1000);
    


    

}