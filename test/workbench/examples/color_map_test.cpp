#include "color_map_test.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/functions/graphics/line.hpp"
#include "../../../src/functions/graphics/polygon.hpp"
#include "../../../src/data/shapes/shapes.hpp"
#include "../../../src/functions/math/sequence.hpp"

#include "../logger.hpp"

#include <iostream>
#include <array>
#include <cstring>
#include <string>

using namespace std;
using namespace logger;
using namespace image;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger) {

        cout << "hello from color map usage" << endl;

        
        // todo test lerp independently


        // 1
        {
            HSV c_0 = HSV(600, 100, 100);
            HSV c_1 = HSV(900);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 1: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 2
        {
            HSV c_0 = HSV(900);
            HSV c_1 = HSV(600, 100, 100);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 2: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 3
        {
            HSV c_0 = HSV(1400);
            HSV c_1 = HSV(100);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 3: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 4
        {
            HSV c_0 = HSV(100);
            HSV c_1 = HSV(1400);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 4: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }




        cout << endl; 




        // DISPLAY some cmaps various LUT sizes
        {
            // Define CMAP - pre LUT size
            HSV color_0(1200, 255, 50);
            HSV color_1(150, 150, 255);
            Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
            Color_Stop stop_1 = Color_Stop(color_1, 1.0f);
            vector<Color_Stop> stops = {stop_0, stop_1};

            vector<int> lut_sizes = {2, 3, 5, 10, 25, 50, 100, 500, 1000};
            
            // DRAW Cmap Col
            Image<RGB> col_canvas = Image<RGB>(Size(1000, 100));
            for (int lut_size : lut_sizes) { 

                string test_name = "Draw Cmap Col - LUT Size: " + to_string(lut_size);
                logger.start(test_name);
                
                Color_Map cmap = Color_Map(stops, lut_size);
                // todo: image object sould return rect at (0, 0) + dx dy
                Rect r = Rect{Point(0, 0), col_canvas.getWidth(), col_canvas.getHeight()};
                draw::polygon::drawCmapCol(col_canvas, r, cmap);

                logger.stop(test_name, col_canvas);
            }


            // DRAW Cmap Row
            Image<RGB> row_canvas = Image<RGB>(Size(100, 1000));
            for (int lut_size : lut_sizes) { 

                string test_name = "Draw Cmap Row - LUT Size: " + to_string(lut_size);
                logger.start(test_name);
                
                Color_Map cmap = Color_Map(stops, lut_size);
                // todo: image object sould return rect at (0, 0) + dx dy
                Rect r = Rect{Point(0, 0), row_canvas.getWidth(), row_canvas.getHeight()};
                draw::polygon::drawCmapRow(row_canvas, r, cmap);

                logger.stop(test_name, row_canvas);
            }

            // todo draw cmap with slope or radial


        }
        
    }





       
    








}