#include "image.hpp"


namespace image { 





    // Conversions 
    // todo swap these out with SIMD optimizations
    

    Image<HSV> toHSV(const Image<RGBA>& original) { 
        Image<HSV> hsv(original.size());

        // --- FUTURE SIMD CODE ---
        // int n = 4; // batch size
        // int simd_ops = original.size() / n
        // for (int i = 0; i < simd_ops; i += n) { 
        //      RGBA2HSV_batch()
        // }
        // int remaining = original.size() - simd_ops * n;
        // for (int i = 0; i < remaining; i++) {
        //      RGBA2HSV();
        // }


        // todo police usage of original as var name
        for (int i = 0; i < original.linearSize(); i++) { 
            hsv.setPixel(i, original.at(i).toHsv());
        }
        return hsv;
    }

    Image<GRAY> toGRAY(const Image<RGBA>& original) { 
        Image<GRAY> gray(original.size());
        for (int i = 0; i < original.linearSize(); i++) { 
            gray.setPixel(i, original.at(i).toGray());
        }
        return gray;
    }

    // todo polymorphic toRGBA needs to handle all types eventually
    // todo should this function allocate memory?
    Image<RGBA> toRGBA(const Image<HSV>& original) { 
        Image<RGBA> rgba(original.size());
        for (int i = 0; i < original.linearSize(); i++) { 
            rgba.setPixel(i, original.at(i).toRgba());
        }
        return rgba;
    }


}