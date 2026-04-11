#include "unit_test_main.hpp"
#include "tests/iterator_unit_test.hpp"
#include "../../src/data/image/io.hpp"
#include <iostream>

using std::cout, std::endl;

namespace unit_test {

    void runAll(string file_system_image_path, string file_system_save_dir) { 
        cout << "running all unit tests" << endl;
        runAllIterator(file_system_image_path);
    }

    void runAllIterator(string image_path) { 
        Image image = io::loadImageFileSystem(image_path);
        iterator::testIterator(image);
    }


}