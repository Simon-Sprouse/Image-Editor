#pragma once

#include "../logger.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace logger;

namespace workbench { 

    void runPrimitives(string image_path, Logger logger);
    void runImage(string image_path, Logger logger);
    void runImageSIMD(string image_path, Logger logger);

    // todo move this to unit tests
    bool rgbImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt);
    bool hsvImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt);

}