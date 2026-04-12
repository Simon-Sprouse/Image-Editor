#pragma once

#include "../../src/data/image/image.hpp"
using namespace image;

#include <string>
using namespace std;

namespace workbench {
    void runGrid(Image image, string save_dir, string window_name);
}