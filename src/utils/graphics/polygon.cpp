#include "polygon.hpp"


namespace draw::polygon {


    void drawRect(Image& image, const Point& tl_corner, int dx, int dy, const Color& color) { 

        // int pointer = image.getLinearIndex(tl_corner);
        // int width = image.getWidth();

        // for (int y = 0; y < dy; y++) { 
        //     for (int x = 0; x < dx; x++) { 
        //         // todo simd
        //         image.setPixel(pointer + x, color);
        //     }
        //     pointer += width;
        // }

        for (auto row : image.regionRows(tl_corner, dx, dy)) { 
            row.fill(color);
        }


    }
}
