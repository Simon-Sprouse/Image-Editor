#include "workbench_main.hpp"
#include "examples/iterator_examples.hpp"
#include "../../src/data/image/io.hpp"

#include <string>
#include <iostream>

using std::cout, std::endl;
using std::string;

namespace workbench { 
    void runAll(string file_system_image_path, string file_system_save_dir) { 
        cout << "running all tests from workbench" << endl;
        runAllIterator(file_system_image_path, file_system_save_dir);
    }

    void runAllIterator(string image_path, string save_dir) { 

        Image image = image::io::loadImageFileSystem(image_path);
        cout << "Loaded image from: " << image_path << endl;
        cout << "Original Dimensions: " << image.size() << endl << endl;

        testIterators(image, save_dir);
    }
}