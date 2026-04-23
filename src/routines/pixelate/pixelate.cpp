#include "pixelate.hpp"
#include "../../utils/math/geometry.hpp"
#include "../../utils/graphics/polygon.hpp"
#include "../../utils/filter/color.hpp"

using namespace image;
using namespace Geometry;

namespace pixelate { 

    void Pixelate::init(const Image& image) {
        original = image.clone();
        canvas = image.clone();


        rect_table_ = rectTableFactory(params_.x_idx, params_.y_idx); // todo: x_idx doesn't sound like enough like a list
    }
    

    Image Pixelate::getCanvas() { 
        return canvas.clone();
    }

    void Pixelate::run() { 
        drawRectAreas();

    }

    void Pixelate::drawRectAreas() { 
        for (Rect rect : rect_table_) { 

            // todo overload with polygon struct
            Color avg_color = filter::color::avgColor(original, rect.tl, rect.dx, rect.dy);

            // todo: namespaceing might be good pattern? because it shows where to find this? 
            draw::polygon::drawRect(canvas, rect.tl, rect.dx, rect.dy, avg_color);

        }
    }
}