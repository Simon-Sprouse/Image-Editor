#pragma once

#include "../logger.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace logger;

namespace workbench { 

    void conversionUsage(string image_path, Logger logger);
    void conversionUnitTest(string image_path, Logger logger);
    void conversionBenchmark(string image_path, Logger logger);


    bool rgbImageCorrectnessTest(const Image<RGB>& test, const cv::Mat& gt, float tolerance = 0.02f);
    bool hsvImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt, float tolerance = 0.02f);

}