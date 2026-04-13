#pragma once

#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <chrono>

#include "../../src/data/image/image.hpp"
using namespace image;

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

namespace logger { 
    class Logger { 
        public: 
            Logger(string window_name, string save_dir) : window_name_(window_name), 
            save_dir_(save_dir) {};
            void start(string task_name);
            void stop(string task_name); // todo maybe think about inversion?
            void stop(string task_name, const Image& output);
        private: 
            string window_name_;
            string save_dir_;
            unordered_map<string, std::pair<TimePoint, TimePoint>> task_times;
            // times
    };
}