#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"

namespace workbench { 

    using namespace image;

    void runAll(string file_system_image_path, string file_system_save_dir);
    void runAllIterator(string image_path, string save_dir);
}