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
        cout << endl;


        // ------------------------
        //      FREE FUNCTIONS
        // ------------------------

        // LERP SINGLE
        {
            HSV c0 = HSV(1400, 255, 0);
            HSV c1 = HSV(100, 0, 100);
            float position = 0.73f;
            HSV lerp_px = lerp(c0, c1, position);

            cout << "LERP SINGLE" << endl;
            cout << "original c0 color: " << c0 << endl;
            cout << "original c1 color: " << c1 << endl;
            cout << "lerp (" << position*100 << "%) color: " << lerp_px << endl;
            cout << endl;
        }


        // LERP MULTI
        {
            HSV c0 = HSV(1400, 255, 0);
            HSV c1 = HSV(100, 0, 100);
            int num_stops = 11;
            vector<HSV> lerp_multi_result = lerpMulti(c0, c1, num_stops);

            cout << "LERP MULTI" << endl;
            for (auto color : lerp_multi_result) { 
                cout << color << endl;
            }
            cout << endl;

        }


        // Color_Map Object 
        // This class should, hide free functions, allow stored consts, abstract discrete maps

        // -----------------
        //   CONSTRUCTORS
        // -----------------

        // Default - HSV fully saturated rainbow gradient
        {

            Color_Map cmap; 
            

            cout << "DEFAULT CONSTRUCTOR" << endl;
            logger.start("Default constructor");
            Image<RGB> display = cmap.display(Size(1000, 100));
            logger.stop("Default constructor", display); // badly need imshow     
            cout << endl;       
        }

        // Two Colors
        {

            HSV color_1(1200, 255, 50);
            HSV color_2(200, 100, 255);
            Color_Map cmap = Color_Map(color_1, color_2);


            cout << "TWO COLOR CONSTRUCTOR" << endl;
            logger.start("Two color constructor");
            Image<RGB> display = cmap.display(Size(1000, 100));
            logger.stop("Two color constructor", display);
            cout << endl;
        }


        // Vector 
        { 
            vector<HSV> colors = {
                HSV(1200, 255, 50),
                HSV(1300, 200, 150),
                HSV(1450, 50, 255)
            };
            Color_Map cmap = Color_Map(colors);


            cout << "VECTOR CONSTRUCTOR" << endl;
            logger.start("Vector constructor");
            Image<RGB> display = cmap.display(Size(1000, 100));
            logger.stop("Vector constructor", display);
            cout << endl;
        }

        // Struct Vector 
        { 
            vector<Color_Stop> color_stops = {
                Color_Stop(HSV(1230, 252, 84), 0.0f),
                Color_Stop(HSV(1126, 170, 120), 0.111f),
                Color_Stop(HSV(986, 140, 137), 0.222f),
                Color_Stop(HSV(872, 167, 142), 0.333f),
                Color_Stop(HSV(797, 187, 142), 0.444f),
                Color_Stop(HSV(725, 205, 158), 0.556f),
                Color_Stop(HSV(645, 181, 183), 0.667f),
                Color_Stop(HSV(464, 146, 206), 0.778f),
                Color_Stop(HSV(314, 206, 222), 0.889f),
                Color_Stop(HSV(229, 218, 253), 1.0f)
            };
            Color_Map cmap = Color_Map(color_stops);


            cout << "STRUCT VECTOR CONSTRUCTOR" << endl;
            logger.start("Struct Vector constructor");
            Image<RGB> display = cmap.display(Size(1000, 100));
            logger.stop("Struct Vector constructor", display);
            cout << endl;
        }


        // ------------------
        //  MEMBER FUNCTIONS
        // ------------------

        // frac
        {
            Color_Map cmap; 
            float track_pos = 0.21;
            RGB px = cmap.frac(track_pos);

            cout << "CONTINUOUS INDEX" << endl;
            cout << "cmap.step(int index, int size)" << endl;
            cout << "cmap (" << track_pos << "%): " << px << endl;
            cout << endl;
        }

        // step
        {
            Color_Map cmap; 
            int index = 6;
            int size = 7;
            RGB px = cmap.step(index, size);

            cout << "DISCRETE INDEX" << endl;
            cout << "cmap.step(int index, int size)" << endl;
            cout << "cmap (" << index+1 << " of " << size <<  "): " << px << endl;
            cout << endl;
        }

        // makeLUT
        {
            Color_Map cmap;
            vector<RGB> LUT = cmap.makeLUT(10);

            cout << "MAKE LUT" << endl;
            cout <<  "cmap.makeLUT(int num_elements)" << endl;
            for (auto px : LUT) { 
                cout << px << endl;
            }
            cout << endl;
        }








        
    }




    void colorMapUnitTest(string image_path, Logger logger) { 

        cout << "Hello from lerp unit test" << endl;
        cout << endl;

        float tolerance = 0.05f;
        HSV c_0;
        HSV c_1;

        // SCENARIO 1 - Positive Linear
        c_0 = HSV(600, 0, 0);
        c_1 = HSV(900, 100, 255);
        assert(lerpTest(c_0, c_1, tolerance));

        // SCENARIO 2 - Negative Linear
        c_0 = HSV(900, 100, 255);
        c_1 = HSV(600, 0, 0);
        assert(lerpTest(c_0, c_1, tolerance));

        // SCENARIO 3 - Positive Wrap Around
        c_0 = HSV(1400, 0, 0);
        c_1 = HSV(100, 100, 255);
        assert(lerpTest(c_0, c_1, tolerance));

        // SCENARIO 4 - Negative Wrap Around
        c_0 = HSV(1400, 0, 0);
        c_1 = HSV(100, 100, 255);
        assert(lerpTest(c_0, c_1, tolerance));

        

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



        // TEST 4 - dedicated lerpMulti function (built from lerp) should match the output from Test 3
        vector<HSV> test_lerp_multi_vector = lerpMulti(color_0, color_1, num_steps);
        if (test_lerp_vector.size() != test_lerp_multi_vector.size()) { 
            cout << "test failed: expecting lerpMulti size to match lerp single (called iteratively)" << endl; 
            return false;
        }

        for (int i = 0; i < test_lerp_multi_vector.size(); i++) { 
            bool test_4 = isWithinTolerance(test_lerp_vector[i], test_lerp_multi_vector[i], tolerance);
            if (!test_4) { 
                cout << "test failed: expecting lerpMulti to match lerp single (called iteratively)" << endl; 
                return false;
            }
        }

        return true;
            
    }


    








}