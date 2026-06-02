#include "color_map.hpp"

namespace image { 


    // FREE FUNCTIONS
    // todo: input validation
    // retuns LUT sub-array - not the most space efficient approach



    HSV lerp(HSV color_0, HSV color_1, float position) { 
        
        // todo input validation position is between 0.0 and 1.0 inclusive

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
        float hue_float = static_cast<float>(h_1 - h_0) * position + h_0;
        float sat_float = static_cast<float>(s_1 - s_0) * position + s_0;
        float val_float = static_cast<float>(v_1 - v_0) * position + v_0;

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
        // TODO - could cache the m calculation for a performance boost rather than calling lerp iteratively
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




    // CONSTRUCTORS

    // default constructor
    Color_Map::Color_Map() { 

        // todo replace with name const
        stops = {
            Color_Stop(HSV(0, 255, 255), 0.0f),
            Color_Stop(HSV(512, 255, 255), 0.33f), 
            Color_Stop(HSV(1024, 255, 255), 0.66f),
            Color_Stop(HSV(1535, 255, 255), 1.0f)
        };
        
    } 



    // METHODS
    RGB Color_Map::frac(float pos) const { 

        // FIND BOUNDS - two pointer march
        int lo_idx = 0;
        int hi_idx = 1;
        while (pos > stops[hi_idx].x_pos) { 
            lo_idx++;
            hi_idx++;
        }  
        Color_Stop lo_stop = stops[lo_idx];
        Color_Stop hi_stop = stops[hi_idx];


        // find position on local track
        float local_track_pos = (pos - lo_stop.x_pos) / (hi_stop.x_pos - lo_stop.x_pos);

        // lerp along local track
        HSV hsv_out = lerp(lo_stop.color, hi_stop.color, local_track_pos);


        // return result as rgb
        // TODO there might be performance boost from returning as hsv, drawing image as hsv, then doing SIMD conversions
        return hsv_out.to<RGB>();
    }

    RGB Color_Map::step(int index, int size) const { 
        float global_track_pos = static_cast<float>(index) / (size - 1);
        return frac(global_track_pos);
    }

    Image<RGB> Color_Map::display(Size size) { 
        Image<RGB> out = Image<RGB>(size);
        // todo refactor when LUT vector is available
        // I know this iteration pattern is bad but I'm avoiding pulling functions into data library

        int w = out.getWidth();
        int h = out.getHeight();
        for (int x = 0; x < w; x++) { 
            RGB px = step(x, w);
            for (int y = 0; y < h; y++) { 
                out.at(x, y) = px;
            }
        }

        return out;
    }


















}