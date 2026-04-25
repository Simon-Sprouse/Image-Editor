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

        // generate sequences and store as axis table
        ax_.x_table = math::sequence::sequenceSelector(params_.seq_x);
        ax_.y_table = math::sequence::sequenceSelector(params_.seq_y);

        // produce rect table from axis table
        rect_table_ = rectTableFactory(ax_); 
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