#include "polygon.hpp"


namespace draw::polygon {


    void drawRect(Image& image, const Rect& rect, const Color& color) { 

        for (auto row : image.regionRows(rect.tl, rect.dx, rect.dy)) { 
            row.fill(color);
        }


    }
}
