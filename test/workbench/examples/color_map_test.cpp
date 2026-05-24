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

        

        HSV color_0(700, 200, 255);
        HSV color_1(900, 150, 200);
        HSV color_2(1200, 255, 100);

        Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
        Color_Stop stop_1 = Color_Stop(color_1, 0.5f);
        Color_Stop stop_2 = Color_Stop(color_2, 1.0f);

        vector<Color_Stop> stops = {stop_0, stop_1, stop_2};

        int side = 1000;
        Image<RGB> img(Size(side, side));


        string test_base_name = "Draw Color Map - LUT Size: ";
        int num_iterations = 100;
        int step = 1;
        int start = 2;
        for (int i = start; i < num_iterations; i += step) { 
            logger.start(test_base_name + to_string(i)); // todo accept multi step tests
            Color_Map cmap = Color_Map(stops, i);
            for (int x = 0; x < img.getWidth(); x++) { 
                draw::line::drawCol(img, x, cmap.frac(x, side).to<RGB>());
            }
            logger.stop(test_base_name + to_string(i), img);
        }
        




    }

}