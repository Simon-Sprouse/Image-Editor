#include "polygon.hpp"

using namespace image;


namespace draw::polygon {


    void drawRect(Image<RGB>& image, const Rect& rect, const RGB& color) { 

        for (auto row : image.regionRows(rect)) { 
            row.fill(color);
        }


    }
}
