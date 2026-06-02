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


        // cout << "testing HSV subraction operator overload" << endl;
        // HSV c0 = HSV(1510, 255, 100);
        // HSV c1 = HSV(1200, 255, 100);
        // float tolerance = 0.1f;
        // bool passing = isWithinTolerance(c0, c1, tolerance);
        // cout << "is within tolerance? : " << passing << endl;
        // cout << endl;



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




    void colorMapUnitTest(string image_path, Logger logger) { 

        cout << "Hello from lerp test" << endl;

        float tolerance = 0.05f;

        // SCENARIO 1
        HSV c_0 = HSV(600, 0, 0);
        HSV c_1 = HSV(900, 100, 255);


        lerpTest(c_0, c_1, tolerance);





    }



    bool lerpTest(HSV color_0, HSV color_1, float tolerance) { 

        // TEST 1 - distance of 0.0f should produce exactly color_0
        HSV lerp_result_1 = lerp(color_0, color_1, 0.0f);
        bool test_1 = isWithinTolerance(lerp_result_1, color_0, tolerance);
        if (!test_1) { 
            cout << "test failed: expecting 0.0f distance to produce leftmost color stop" << endl;
            return false;
        }

        // TEST 2 - distance of 1.0f should produce exactly color_1
        HSV lerp_result_2 = lerp(color_0, color_1, 1.0f);
        bool test_2 = isWithinTolerance(lerp_result_2, color_1, tolerance);
        if (!test_2) { 
            cout << "test failed: expecting 1.0f distance to produce rightmost color stop" << endl;
            return false;
        }



        // TEST 3 - multiple steps should all be within the same interval of each other
        // this logic will be similar to the lerpMultiTest but that's fine
        int num_steps = 10;
        float step_size = 1.0f / static_cast<float>(num_steps);

        vector<HSV> test_lerp_vector;
        test_lerp_vector.reserve(num_steps);

        vector<float> distances = math::sequence::uniformIntervalsUnit(10);
        for (auto distance : distances) { 
            HSV lerp_result = lerp(color_0, color_1, distance);
            test_lerp_vector.push_back(lerp_result);
        }

        for (int i = 0; i < test_lerp_vector.size() - 1; i++) { 
            HSV current = test_lerp_vector[i];
            HSV next = test_lerp_vector[i+1];
            float adjusted_tolerance = step_size + tolerance; // we already expect <step_size> worth of distance
            bool test_3 = isWithinTolerance(lerp_result_2, color_1, adjusted_tolerance);
            if (!test_3) { 
                cout << "test failed: expecting distance between color steps to be uniform" << endl;
                return false;
            }
        }


        return true;
            
    }
       
    








}