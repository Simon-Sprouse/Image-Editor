#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"
#include "logger.hpp"

namespace workbench { 

    using namespace image;
    using logger::Logger;

    // todo - I don't like these names upon re-reading w/ new context
    void runAll(string image_path, Logger& logger);
    void runWorkbench(string image_path, string save_dir);
    
}