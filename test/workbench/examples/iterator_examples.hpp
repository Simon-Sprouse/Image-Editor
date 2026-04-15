#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"
#include "../logger.hpp"

namespace workbench { 

    using namespace image;
    using logger::Logger;

    void runIterator(string image_path, Logger logger);
}