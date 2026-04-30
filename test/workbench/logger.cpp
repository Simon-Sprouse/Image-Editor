#include "logger.hpp"
#include <chrono>

#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"
using namespace image;

#include <opencv2/opencv.hpp>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

#include <iostream>
using std::cout, std::endl, std::setw;

namespace logger { 

    // todo, should we get access to the insides of classes? can we do that with a helper class? What's the best way to do that? 

    void Logger::initCV() { 
        // todo should logger own this? 
        cv::namedWindow(window_name_, cv::WINDOW_NORMAL);
        cv::resizeWindow(window_name_, cv::Size(100, 100));
    }


    void Logger::start(string task_name) { 

        // todo make it clear that task_name is a key and enforce uniqueness
        TimePoint start_time = Clock::now();
        task_times[task_name].first = start_time; // we will set the end time later

        // print header or something


    }

    void Logger::stopTimer_(string task_name) { 
        TimePoint stop_time = Clock::now();
        task_times[task_name].second = stop_time; 
    }
    void Logger::printTime_(string task_name) { 
        std::chrono::duration<double> elapsed = task_times[task_name].second - task_times[task_name].first;


        // Todo make this more elegant once it's extended. 
        cout << 
        "Task: " << task_name << setw(15) << 
        " time: " << elapsed.count() << " s" 
        << endl << endl;
    }

    void Logger::blockCV_() { 
        // allow user to exit workbench (escape or q) or continue (anything else)
        int key = cv::waitKey(0);
        if (key == 'q' || key == 27) { 
            throw UserEscapeSignal();
        }

    }

    void Logger::stop(string task_name) { 
        stopTimer_(task_name);
        printTime_(task_name);
        blockCV_();
    }

    void Logger::stop(string task_name, const Image& output) { 

        stopTimer_(task_name);
        printTime_(task_name);

        
        cv::setWindowTitle(window_name_, task_name);
        cv::Mat output_mat = io::imageToCvMat(output);
        cv::imshow(window_name_, output_mat);

        int key = cv::waitKey(0);
        if (key == 'q' || key == 27) { 
            throw UserEscapeSignal();
        }
        else if (key == 's') { 
            // todo: this is disgusting, fix dir, strip whitespace
            // todo: probably best to invoke from image::io
            // todo: write to console when saving
            cv::imwrite("../results/" + task_name + ".jpg", output_mat);
        }


    }





}