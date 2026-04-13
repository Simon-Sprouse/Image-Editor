#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"
#include "logger.hpp"

namespace workbench { 

    using namespace image;
    using logger::Logger;

    void runAll(string image_path, Logger& logger);
    void runWorkbench(string image_path, string save_dir);
    
}