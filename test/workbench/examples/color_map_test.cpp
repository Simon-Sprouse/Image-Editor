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





        // FREE FUNCTION - LERP SINGLE
        {
            vector<float> distances = math::sequence::uniformIntervalsUnit(7);

            // SCENARIO 1 - Positive Linear
            {
                HSV c_0 = HSV(600, 100, 100);
                HSV c_1 = HSV(900, 255, 0);

                cout << "color 0: " << c_0 << endl;
                cout << "color 1: " << c_1 << endl;

                for (auto distance : distances) { 
                    HSV c_lerp = lerp(c_0, c_1, distance);
                    cout << c_lerp << endl;
                }
                cout << endl;
            }

            // SCENARIO 2 - Negative Linear
            {
                HSV c_0 = HSV(900, 255, 0);
                HSV c_1 = HSV(600, 100, 100);

                cout << "color 0: " << c_0 << endl;
                cout << "color 1: " << c_1 << endl;

                for (auto distance : distances) { 
                    HSV c_lerp = lerp(c_0, c_1, distance);
                    cout << c_lerp << endl;
                }
                cout << endl;
            }

            // SCENARIO 3 - Positive Wrap
            {
                

                HSV c_0 = HSV(1400, 255, 0);
                HSV c_1 = HSV(100, 100, 100);

                cout << "color 0: " << c_0 << endl;
                cout << "color 1: " << c_1 << endl;

                for (auto distance : distances) { 
                    HSV c_lerp = lerp(c_0, c_1, distance);
                    cout << c_lerp << endl;
                }
                cout << endl;
            }

            // SCENARIO 4 - Negative Wrap
            {
                
                HSV c_0 = HSV(100, 100, 100);
                HSV c_1 = HSV(1400, 255, 0);

                cout << "color 0: " << c_0 << endl;
                cout << "color 1: " << c_1 << endl;

                for (auto distance : distances) { 
                    HSV c_lerp = lerp(c_0, c_1, distance);
                    cout << c_lerp << endl;
                }
                cout << endl;
            }
            

            
        }

























        // DISPLAY some cmaps various LUT sizes
        {

            vector<int> lut_sizes = {2, 3, 5, 10, 25, 50, 100, 500, 1000};
            
            // DRAW Cmap Col
            Image<RGB> col_canvas = Image<RGB>(Size(1000, 100));
            for (int lut_size : lut_sizes) { 

                string test_name = "Draw Cmap Col - LUT Size: " + to_string(lut_size);
                logger.start(test_name);
                
                Color_Map cmap = Color_Map(COSMOS_STOPS, lut_size);
                // todo: image object sould return rect at (0, 0) + dx dy
                Rect r = Rect{Point(0, 0), col_canvas.getWidth(), col_canvas.getHeight()};
                draw::polygon::drawCmapCol(col_canvas, r, cmap); // todo scope these consts

                logger.stop(test_name, col_canvas);
            }


            // DRAW Cmap Row
            Image<RGB> row_canvas = Image<RGB>(Size(100, 1000));
            for (int lut_size : lut_sizes) { 

                string test_name = "Draw Cmap Row - LUT Size: " + to_string(lut_size);
                logger.start(test_name);
                
                // TODO elegant cmap behavior when num stops is greater than LUT size, needs work
                Color_Map cmap = Color_Map(VIRIDIS_STOPS, lut_size);
                // todo: image object sould return rect at (0, 0) + dx dy
                Rect r = Rect{Point(0, 0), row_canvas.getWidth(), row_canvas.getHeight()};
                draw::polygon::drawCmapRow(row_canvas, r, cmap);

                logger.stop(test_name, row_canvas);
            }

            // todo draw cmap with slope or radial

        }



        // TEST SOME CONST CMAP's
        {
            

            Image<RGB> canvas = Image<RGB>(Size(1000, 100));
            Rect r = Rect{Point(0, 0), canvas.getWidth(), canvas.getHeight()};
            string test_base_name = "const cmap: ";

            logger.start(test_base_name + "VIRIDIS");
            draw::polygon::drawCmapCol(canvas, r, VIRIDIS);
            logger.stop(test_base_name + "VIRIDIS", canvas);

            logger.start(test_base_name + "COSMOS");
            draw::polygon::drawCmapCol(canvas, r, COSMOS);
            logger.stop(test_base_name + "COSMOS", canvas);

        }











        
    }





       
    








}