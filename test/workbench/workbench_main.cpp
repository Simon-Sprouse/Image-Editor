#include "workbench_main.hpp"
#include "examples/iterator_examples.hpp"

#include <string>
#include <iostream>

using std::cout, std::endl;
using std::string;

namespace workbench { 
    void runAll(string file_system_image_path, string file_system_save_dir) { 
        cout << "running all tests from workbench" << endl;
        testIterators(file_system_image_path, file_system_save_dir);
    }
}