#include "polygon.hpp"

using namespace image;


namespace draw::polygon {


    void drawRect(Image<RGBA>& image, const Rect& rect, const RGBA& color) { 

        for (auto row : image.regionRows(rect)) { 
            row.fill(color);
        }


    }
}
