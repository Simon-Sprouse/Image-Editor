#pragma once

#include <string>
#include "../logger.hpp"

using namespace logger;
using namespace std;

namespace workbench { 
    void runPixelate(string image_path, Logger logger);
    void runGrid(string image_path, Logger logger);
}