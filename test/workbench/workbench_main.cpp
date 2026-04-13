#include "workbench_main.hpp"
#include "examples/iterator_examples.hpp"
#include "examples/grid_workbench.hpp"
#include "../../src/data/image/io.hpp"
#include "logger.hpp"

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using std::cout, std::endl;
using std::string;
using logger::Logger;

namespace workbench { 
    void runAll(string file_system_image_path, string file_system_save_dir) { 
        cout << "running all tests from workbench" << endl;
        // runAllIterator(file_system_image_path, file_system_save_dir);



        string window_name = "workbench_window"; // the first name passed to namedWindow is immutable and is used for id

        // todo should logger own this? 
        cv::namedWindow(window_name, cv::WINDOW_NORMAL);
        cv::resizeWindow(window_name, cv::Size(100, 100));

        Logger my_logger(window_name, file_system_save_dir);
        runGrid(file_system_image_path, my_logger);


        cv::destroyAllWindows();



    }

    void runAllIterator(string image_path, string save_dir) { 

        Image image = image::io::loadImageFileSystem(image_path);
        cout << "Loaded image from: " << image_path << endl;
        cout << "Original Dimensions: " << image.size() << endl << endl;

        testIterators(image, save_dir);
    }


}