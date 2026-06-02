#pragma once

#include "../logger.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/data/image/primitives.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace logger;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger);
    void colorMapUnitTest(string image_path, Logger logger);

    bool lerpTest(HSV color_0, HSV color_1, float tolerance);
}