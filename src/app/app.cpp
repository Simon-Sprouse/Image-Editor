#include <iostream>

#include "app.hpp"
#include "../data/image/io.hpp"
#include "run_mosaic.hpp"
#include "run_pop_art.hpp"

#include <opencv2/opencv.hpp>

using std::cout, std:: endl;

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

        ImageResult result;


        while (running) { 
            key = cv::waitKey(30);

            if (key == 'q' || key == 27) { 
                running = false;
            }
            else if (key == '1') { 
                result = runMosaic(image);
            }
            else if (key == '2') { 
                result = runPopArt(image);
            }

            if (!result.empty()) { 
                cv::imshow(window_name, image::io::imageToCvMat(result.image));
                cv::setWindowTitle(window_name, result.label);
            }
            
    
        }

        cv::destroyAllWindows();

    }



}