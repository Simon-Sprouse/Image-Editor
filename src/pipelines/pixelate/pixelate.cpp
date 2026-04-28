#include "pixelate.hpp"
#include "../../functions/math/geometry.hpp"
#include "../../functions/graphics/polygon.hpp"
#include "../../functions/filter/color.hpp"

using namespace image;
using namespace Geometry;

#include <iostream>
#include <algorithm>
using namespace std;


namespace pixelate { 

    void Pixelate::init(Cache& cache) {

        // implies original is set by caller -- todo: is this good? 
        cache.canvas = cache.original.clone();

        // generate sequences and store as axis table
        cache.ax.x_table = variant_fn::sequenceFn(params.seq_x_common);
        cache.ax.y_table = variant_fn::sequenceFn(params.seq_y_common);

        // todo: handle unsorted sequences
        std::sort(cache.ax.x_table.begin(), cache.ax.x_table.end());
        std::sort(cache.ax.y_table.begin(), cache.ax.y_table.end());

        

        // produce rect table from axis table
        cache.rect_table = rectTableFactory(cache.ax); 

        cout << "Rect table:" << endl;
        shapes::printVectorNewline<shapes::Rect>(cache.rect_table);
    }
    

    void Pixelate::run(Cache& cache) { 
        drawRectAreas(cache.original, cache.canvas, cache.rect_table);
    }

    void Pixelate::drawRectAreas(const Image& original, Image& canvas, const vector<Rect>& rect_table) { 
        for (Rect rect : rect_table) { 

            cout << rect << endl;

            // todo overload with polygon struct
            Color avg_color = filter::color::avgColor(original, rect);


            // todo: namespaceing might be good pattern? because it shows where to find this? 
            draw::polygon::drawRect(canvas, rect, avg_color);

            cout << endl;
        }
    }
}