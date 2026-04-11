#pragma once

#include <string>
using std::string;

#include "../../src/data/image/image.hpp"
using namespace image;

namespace unit_test {
    void runAll(string file_system_image_path, string file_system_save_dir);


    void runAllIterator(string image_path);
}