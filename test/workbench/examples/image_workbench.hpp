#pragma once

#include "../logger.hpp"

using namespace std;
using namespace logger;

namespace workbench { 

    void runPrimitives(string image_path, Logger logger);
    void runImage(string image_path, Logger logger);
    void runImageSIMD(string image_path, Logger logger);

}