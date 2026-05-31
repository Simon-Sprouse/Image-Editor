#include "image.hpp"
#include <arm_neon.h>


namespace image { 

    // // copy region todo: should live in image ecosystem
    // void copyRegion(const Image<RGB>& src_img, Image<RGB>& dst_img, Point tl) { 
    //     // todo input validation
    //     int row_size = src_img.getWidth();
    //     for (int y = 0; y < src_img.getHeight(); y++) { 
    //         const RGB* src_ptr = src_img.rowPtr(y);
    //         RGB* dst_ptr = dst_img.rowPtr(y + tl.y) + tl.x;
    //         std::memcpy(dst_ptr, src_ptr, sizeof(RGB)*row_size);
    //     }
    // }







}