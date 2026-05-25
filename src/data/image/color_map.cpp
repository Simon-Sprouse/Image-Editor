#include "color_map.hpp"

namespace image { 


    // CONSTRUCTORS
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


    // FREE FUNCTIONS
    // todo: input validation
    // retuns LUT sub-array - not the most space efficient approach
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

    // This function gives LUT index given a float from 0-1. Todo input validation
    int getIdxFromXPos(float x_pos, int N) { 
        int idx = static_cast<int>(x_pos * N);
        if (idx > N-1) { 
            idx = N-1;
        }
        return idx;
    }









}