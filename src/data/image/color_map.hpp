#pragma once 

#include "primitives.hpp"
#include "pixel.hpp"

#include <array>
#include <vector>
#include <cstring> // for std::memcpy
#include <iostream>

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

        HSV at(int i) { 
            return lut[i]; 
        }
        HSV frac(float f) { 
            return lut[static_cast<int>(N * f)]; 
        }
        HSV frac(int i, int total) { 
            // todo: input validation i <= total
            float track_pos = (static_cast<float>(i) / total) * N;
            cout << "track_pos: " << track_pos << endl;
            return lut[static_cast<int>(track_pos)];
        }



        vector<Color_Stop> stops;
        vector<HSV> lut;
        int N;
    };



    // todo: move to cpp
    // Free functions - not the most space efficient approach
    inline vector<HSV> lerpMulti(HSV color_0, HSV color_1, int num_steps) { 

        // todo input validation, potential for divide by zero

        vector<HSV> out;
        out.reserve(num_steps);

        for (int i = 0; i < num_steps; i++) { 

            // todo define multiplication and addition at struct level
            // determine coefficients for blending
            // new_color = (w_0 * color_0) + (w_1 * color_1)
            float w_0 = static_cast<float>(num_steps - i) / num_steps;
            float w_1 = 1.0f - w_0;

            // HSV new_color = (w_0 * color_0) + (w_1 * color_1);
            HSV new_color = HSV(
                ((color_0.h * w_0) + (color_1.h * w_1)),
                ((color_0.s * w_0) + (color_1.s * w_1)), 
                ((color_0.v * w_0) + (color_1.v * w_1))
            );

            out.push_back(new_color);


        }

        return out;

    }


    Color_Map::Color_Map(vector<Color_Stop> _stops, int _N) : stops(_stops), N(_N) { 

        // todo: input validation, must have at least two stops
        // todo: are stops already sorted by x_pos? 

        lut.reserve(N);

        for (int i = 0; i < stops.size() - 1; i++) { 
            Color_Stop current_stop = stops.at(i);
            Color_Stop next_stop = stops.at(i + 1);

            int starting_pos = static_cast<int>(N * current_stop.x_pos);

            float track_distance = next_stop.x_pos - current_stop.x_pos; // between 0.0 and 1.0
            int num_elements_for_segment = static_cast<int>(N * track_distance);
            vector<HSV> lut_elements = lerpMulti(current_stop.color, next_stop.color, num_elements_for_segment);

            std::memcpy(lut.data() + starting_pos, lut_elements.data(), num_elements_for_segment * sizeof(HSV));

        }



    } 





}