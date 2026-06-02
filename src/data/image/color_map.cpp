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



    HSV lerp(HSV color_0, HSV color_1, float distance) { 
        
        // todo input validation distance is between 0.0 and 1.0 inclusive

        uint16_t h_0 = color_0.h;
        uint8_t s_0 = color_0.s;
        uint8_t v_0 = color_0.v;

        uint16_t h_1 = color_1.h;
        uint8_t s_1 = color_1.s;
        uint8_t v_1 = color_1.v;

        int track_abs = std::abs(h_1 - h_0);
        int track_wrap = 1536 - track_abs;

        if (track_wrap < track_abs) { 
            if (h_0 < h_1) { 
                h_0 += 1536;
            }
            else {
                h_1 += 1536;
            }
        }

        // lerp y = m * x + b
        float hue_float = static_cast<float>(h_1 - h_0) * distance + h_0;
        float sat_float = static_cast<float>(s_1 - s_0) * distance + s_0;
        float val_float = static_cast<float>(v_1 - v_0) * distance + v_0;

        uint16_t h = static_cast<uint16_t>(hue_float) % 1536;
        uint8_t s = static_cast<uint8_t>(sat_float);
        uint8_t v = static_cast<uint8_t>(val_float);

        return HSV(h, s, v);
    }



    vector<HSV> lerpMulti(HSV color_0, HSV color_1, int num_stops) { 

        // universal
        vector<HSV> out;
        out.reserve(num_stops);

        // TODO - this logic was copy pasted from math::sequence to avoid circularity
        // compute distances along unit vector: 
        vector<float> distances;
        distances.reserve(num_stops);
        float step = 1.0f / (num_stops - 1); // the -1 is becase we return bounded sequence
        for (int i = 0; i < num_stops; i++) { 
            distances.push_back(static_cast<float>(i) * step);
        }
        distances.at(distances.size()-1) = 1.0f;


        for (float distance : distances) { 
            HSV lerp_result = lerp(color_0, color_1, distance);
            out.push_back(lerp_result);
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