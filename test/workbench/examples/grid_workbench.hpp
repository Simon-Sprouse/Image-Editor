#pragma once

#include "../../src/data/image/image.hpp"
using namespace image;

#include "../logger.hpp"


#include <string>
using namespace std;

namespace workbench {

    using logger::Logger;

    void runGrid(string image_path, Logger logger);
}