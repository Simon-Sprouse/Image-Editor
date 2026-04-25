#include "pixelate.hpp"
#include "../../utils/math/geometry.hpp"
#include "../../utils/graphics/polygon.hpp"
#include "../../utils/filter/color.hpp"

using namespace image;
using namespace Geometry;


namespace pixelate { 

    void Pixelate::init(Cache& cache) {

        // implies original is set by caller -- todo: is this good? 
        cache.canvas = cache.original.clone();

        // generate sequences and store as axis table
        cache.ax.x_table = math::sequence::sequenceSelector(params.seq_x);
        cache.ax.y_table = math::sequence::sequenceSelector(params.seq_y);

        // produce rect table from axis table
        cache.rect_table = rectTableFactory(cache.ax); 
    }
    

    void Pixelate::run(Cache& cache) { 
        drawRectAreas(cache.original, cache.canvas, cache.rect_table);
    }

    void Pixelate::drawRectAreas(const Image& original, Image& canvas, const vector<Rect>& rect_table) { 
        for (Rect rect : rect_table) { 

            // todo overload with polygon struct
            Color avg_color = filter::color::avgColor(original, rect);

            // todo: namespaceing might be good pattern? because it shows where to find this? 
            draw::polygon::drawRect(canvas, rect, avg_color);
        }
    }
}