#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"

namespace workbench { 

    using namespace image;

    void testIterators(Image& image, string save_dir);
}