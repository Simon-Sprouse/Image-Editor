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




        // DISPLAY some cmaps
        {
            HSV color_0(1200, 255, 50);
            HSV color_1(150, 150, 255);


            Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
            Color_Stop stop_1 = Color_Stop(color_1, 1.0f);

            vector<Color_Stop> stops = {stop_0, stop_1};

            int side = 1000;
            Image<RGB> img(Size(side, side));


            string cmap_base_name = "Create Color Map - LUT Size: ";
            string draw_base_name = "Draw Color Map - LUT Size: ";
            int num_iterations = 3;
            int step = 3;
            int start = 2;
            for (int i = start; i < num_iterations*step; i += step) { 

                Color_Map cmap = Color_Map(stops, i);

                logger.start(draw_base_name + to_string(i));
                for (int x = 0; x < img.getWidth(); x++) { 
                    draw::line::drawCol(img, x, cmap.frac(x, side).to<RGB>());
                }
                logger.stop(draw_base_name + to_string(i), img);
                cout << endl;
            }
        }
        
    }





       
    


    // create column image
    Image<RGB> makeColumnImg(Size size, const Color_Map& cmap) { 
        Image<RGB> img(size);
        for (int x = 0; x < size.width; x++) { 
            draw::line::drawCol(img, x, cmap.frac(x, size.width).to<RGB>());
        }
        return img;
    }

    // todo these could be way more efficient
    Image<RGB> makeRowImg(Size size, const Color_Map& cmap) { 
        Image<RGB> img(size);
        for (int y = 0; y < size.height; y++) { 
            draw::line::drawRow(img, y, cmap.frac(y, size.height).to<RGB>());
        }
        return img;
    }








}