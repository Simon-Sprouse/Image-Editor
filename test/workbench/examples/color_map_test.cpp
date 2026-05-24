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

        

        HSV color_0(900, 255, 127);
        HSV color_1(700, 255, 255);

        Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
        Color_Stop stop_1 = Color_Stop(color_1, 1.0f);

        vector<Color_Stop> stops = {stop_0, stop_1};

        


        logger.start("Draw cmap - LUT size 7");
        {
            Color_Map cmap = Color_Map<7>(stops);
            Image<RGB> test_img(Size(1000, 1000));

            for (int i = 0; i < 1000; i++) { 
                draw::line::drawCol(test_img, i, cmap.frac(i, 1000).to<RGB>());
            }

            logger.stop("Draw cmap - LUT size 7", test_img);
        }

        logger.start("Draw cmap - LUT size 777");
        {
            Color_Map cmap = Color_Map<777>(stops);
            Image<RGB> test_img(Size(1000, 1000));

            for (int i = 0; i < 1000; i++) { 
                draw::line::drawCol(test_img, i, cmap.frac(i, 1000).to<RGB>());
            }

            logger.stop("Draw cmap - LUT size 777", test_img);
        }


    }

}