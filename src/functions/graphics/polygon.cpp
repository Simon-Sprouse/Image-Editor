#include "polygon.hpp"


namespace draw::polygon {


    void drawRect(Image& image, const Rect& rect, const RGBA& color) { 

        for (auto row : image.regionRows(rect)) { 
            row.fill(color);
        }


    }
}
