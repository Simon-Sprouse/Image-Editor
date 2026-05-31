#include "polygon.hpp"

using namespace image;


namespace draw::polygon {


    void drawRect(Image<RGB>& image, const Rect& rect, const RGB& color) { 

        for (auto row : image.regionRows(rect)) { 
            row.fill(color);
        }


    }

     
    void drawCmapCol(Image<RGB>& canvas, shapes::Rect rect, const Color_Map& cmap) { 
        for (int x = 0; x < rect.dx; x++) { 
            Rect r = Rect{Point(rect.tl.x + x, rect.tl.y), 1, rect.dy};
            drawRect(canvas, r, cmap.frac(x, rect.dx).to<RGB>());
        }
    }

    void drawCmapRow(Image<RGB>& canvas, shapes::Rect rect, const Color_Map& cmap) { 
        for (int y = 0; y < rect.dy; y++) { 
            Rect r = Rect{Point(rect.tl.x, rect.tl.y + y), rect.dx, 1};
            drawRect(canvas, r, cmap.frac(y, rect.dy).to<RGB>());
        }
    }


}
