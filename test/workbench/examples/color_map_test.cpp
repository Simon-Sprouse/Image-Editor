#include "color_map_test.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/functions/graphics/line.hpp"
#include "../../../src/functions/graphics/polygon.hpp"
#include "../../../src/data/shapes/shapes.hpp"

#include "../logger.hpp"

#include <iostream>
#include <array>

using namespace std;
using namespace logger;
using namespace image;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger) {

        cout << "hello from color map usage" << endl;

        
        // todo test lerp independently

        HSV color_0(0, 200, 50);
        HSV color_1(50, 255, 150);
        HSV color_2(100, 255, 200);
        HSV color_3(150, 100, 255);

        Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
        Color_Stop stop_1 = Color_Stop(color_1, 0.4f);
        Color_Stop stop_2 = Color_Stop(color_2, 0.65f);
        Color_Stop stop_3 = Color_Stop(color_3, 1.0f);

        vector<Color_Stop> stops = {stop_0, stop_1, stop_2, stop_3};

        int side = 1000;
        Image<RGB> img(Size(side, side));


        string cmap_base_name = "Create Color Map - LUT Size: ";
        string draw_base_name = "Draw Color Map - LUT Size: ";
        int num_iterations = 100;
        int step = 1;
        int start = 2;
        for (int i = start; i < num_iterations; i += step) { 

            logger.start(cmap_base_name + to_string(i)); // todo accept multi step tests
            Color_Map cmap = Color_Map(stops, i);
            logger.stop(cmap_base_name + to_string(i)); // todo, non-blocking timers (no keypress)

            logger.start(draw_base_name + to_string(i));
            for (int x = 0; x < img.getWidth(); x++) { 
                draw::line::drawCol(img, x, cmap.frac(x, side).to<RGB>());
            }
            logger.stop(draw_base_name + to_string(i), img);
            cout << endl;
        }
        




    }

}