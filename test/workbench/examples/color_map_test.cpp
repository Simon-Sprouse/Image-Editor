#include "color_map_test.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/functions/graphics/line.hpp"

#include "../logger.hpp"

#include <iostream>
#include <array>

using namespace std;
using namespace logger;
using namespace image;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger) {

        cout << "hello from color map usage" << endl;

        Color_Stop my_color_stop = Color_Stop{HSV(777, 255, 255), 0.73f};




        HSV c0(0, 255, 255);
        HSV c1(1535, 255, 255);

        std::array<HSV, 100> arr;

        for (int i = 0; i < arr.size(); i++) { 
            float pct_0 = (float)(arr.size() - i) / arr.size();
            float pct_1 = (float)i / arr.size();

            cout << "i: " << i << "   p0:" << pct_0 << "   p1:" << pct_1 << endl;
        }


        for (int i = 0; i < arr.size(); i++) { 
            float pct_0 = (float)(arr.size() - i) / arr.size();
            float pct_1 = (float)i / arr.size();

            // todo move some of this math into HSV struct
            HSV new_color = HSV(
                c0.h * pct_0 + c1.h * pct_1,
                c0.s * pct_0 + c1.s * pct_1, 
                c0.v * pct_0 + c1.v * pct_1
            );

            cout << "i: " << i << " new_hsv: " << new_color << endl;

            arr[i] = new_color;

        }



        logger.start("Draw cmap");
        Image<RGB> test_color_map(Size(100, 100));
        for (int i = 0; i < arr.size(); i++) { 
            draw::line::drawCol(test_color_map, i, arr[i].to<RGB>());
        }
        logger.stop("Draw cmap", test_color_map);












    }

}