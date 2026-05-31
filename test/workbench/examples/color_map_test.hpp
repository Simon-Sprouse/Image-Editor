#pragma once

#include "../logger.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/data/image/primitives.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace logger;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger);

}