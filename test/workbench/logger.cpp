#include "logger.hpp"
#include <chrono>

#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"
using namespace image;

#include <opencv2/opencv.hpp>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

#include <iostream>
using std::cout, std::endl;

namespace logger { 


    void Logger::start(string task_name) { 

        // todo make it clear that task_name is a key and enforce uniqueness
        TimePoint start_time = Clock::now();
        task_times[task_name].first = start_time; // we will set the end time later

        // print header or something


    }

    void Logger::stop(string task_name) { 
        // todo think about handling tasks that weren't started
        TimePoint stop_time = Clock::now();
        task_times[task_name].second = stop_time; // we will set the end time later

        // todo make this a function for printing
        std::chrono::duration<double> elapsed = stop_time - task_times[task_name].first;
        cout << "Task: " << task_name << " time: " << elapsed.count() << " s" << endl;
    }

    void Logger::stop(string task_name, const Image& output) { 

        stop(task_name); // handle timer

        cv::setWindowTitle(window_name_, task_name);
        cv::imshow(window_name_, io::imageToCvMat(output));
        cv::waitKey(0);



    }





}