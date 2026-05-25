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

        HSV at(int i) { 
            return lut[i]; 
        }
        HSV frac(float f) { 
            return lut[static_cast<int>(N * f)]; 
        }
        HSV frac(int i, int total) { 
            // todo: input validation i <= total
            float track_pos = (static_cast<float>(i) / (total-1)) * N;
            // cout << "track_pos: " << track_pos << endl;
            return lut[static_cast<int>(track_pos)];
        }



        vector<Color_Stop> stops;
        vector<HSV> lut;
        int N;
    };

    


    // todo: move to cpp
    // todo: input validation
    // Free functions - not the most space efficient approach
    inline vector<HSV> lerpMulti(HSV color_0, HSV color_1, int num_steps) { 

        // universal
        vector<HSV> out;
        out.reserve(num_steps);

        int distance = std::abs(color_1.h - color_0.h);
        int distance_wrap = 1536 - distance;

        uint16_t h_0 = color_0.h;
        uint8_t s_0 = color_0.s;
        uint8_t v_0 = color_0.v;

        uint16_t h_1 = color_1.h;
        uint8_t s_1 = color_1.s;
        uint8_t v_1 = color_1.v;

        if (distance_wrap < distance) { 
            if (h_0 < h_1) { 
                h_0 += 1536;
            }
            else {
                h_1 += 1536;
            }
        }

        float hue_step = static_cast<float>(h_1 - h_0) / (num_steps - 1);
        float sat_step = static_cast<float>(s_1 - s_0) / (num_steps - 1);
        float val_step = static_cast<float>(v_1 - v_0) / (num_steps - 1);

        for (int i = 0; i < num_steps; i++) { 
            HSV new_color = HSV(
                (static_cast<uint16_t>(h_0 + (hue_step * i)) % 1536),
                (s_0 + (sat_step * i)), 
                (v_0 + (val_step * i))
            );
            out.push_back(new_color);
        }

        return out;
    }



    int getIdxFromXPos(float x_pos, int N) { 
        int idx = static_cast<int>(x_pos * N);
        if (idx > N-1) { 
            idx = N-1;
        }
        return idx;
    }


    Color_Map::Color_Map(vector<Color_Stop> _stops, int _N) : stops(_stops), N(_N) { 

        // todo: input validation, must have at least two stops

        lut.reserve(N);

        std::sort(
            stops.begin(), 
            stops.end(), 
            [](Color_Stop lhs, Color_Stop rhs) { return lhs.x_pos < rhs.x_pos; }
        );


        for (int i = 0; i < stops.size()-1; i++) { 
            int current_idx = getIdxFromXPos(stops.at(i).x_pos, N);
            int next_idx = getIdxFromXPos(stops.at(i+1).x_pos, N);
            int num_elements = (next_idx - current_idx) + 1;
            if (num_elements == 1) { 
                continue;
            }
            vector<HSV> lerp_elements = lerpMulti(stops.at(i).color, stops.at(i+1).color, num_elements);
            std::memcpy(lut.data() + current_idx, lerp_elements.data(), num_elements * sizeof(HSV));
        }
        
    } 

}