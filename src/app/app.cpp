#include <iostream>
#include <chrono>

#include "app.hpp"
#include "../data/image/io.hpp"
#include "run_routines.hpp"

#include <opencv2/opencv.hpp>

using std::cout, std:: endl;
using image::Color, image::Point, image::RowIterator, image::RegionRowIterator;

namespace app {


    

    void mainLoop(string image_path, string save_dir) { 



        Image image = image::io::loadImageFileSystem(image_path);
        cout << "Loaded image from: " << image_path << endl;
        cout << "Original Dimensions: " << image.size() << endl;



        bool running = true;
        int key = -1;
        string window_name = "test_window"; // the first name passed to namedWindow is immutable and is used for id
        string display_name;                // this tracks display title but doesn't change id

        cv::namedWindow(window_name, cv::WINDOW_NORMAL);
        cv::resizeWindow(window_name, cv::Size(100, 100));

        


        while (running) { 
            ImageResult result;
            key = cv::waitKey(30);
            auto start = std::chrono::high_resolution_clock::now();


            if (key == 'q' || key == 27) { 
                running = false;
            }
            else if (key == '1') { 
                result.image = image;
                result.label = "original";
            }
            else if (key == '2') { 
                result = runMosaic(image);
            }
            else if (key == '3') { 
                result = runPopArt(image);
            }
            else if (key == '4') { 
                result = runPopArtSlow(image);
            }
            else if (key == '5') { 
                result = runGrid(image);
            }


            if (!result.empty()) { 
                cv::imshow(window_name, image::io::imageToCvMat(result.image));
                cv::setWindowTitle(window_name, result.label);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                cout << "Function execution time: " << elapsed.count() << " s" << endl;
            }
            
    
        }

        cv::destroyAllWindows();

    }



}