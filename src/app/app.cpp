#include <iostream>
#include <chrono>

#include "app.hpp"
#include "../data/image/io.hpp"
#include "run_routines.hpp"

#include <opencv2/opencv.hpp>

using std::cout, std:: endl;
using image::Color, image::Point, image::RowIterator, image::RegionRowIterator;

namespace app {


    void testIterators(string image_path, string save_dir) { 



        Image image = image::io::loadImageFileSystem(image_path);
        cout << "Loaded image from: " << image_path << endl;
        cout << "Original Dimensions: " << image.size() << endl << endl;

        Color* data = image.data();
        cout << "You can now get pointer access to the linear start" << endl;
        cout << "image.data(): " << image.data() << endl << endl;

        Color* begin = image.begin();
        Color* end = image.end();
        cout << "Now we have access to begin() and end() methods." << endl;
        cout << "image.begin(): " << image.begin() << endl;
        cout << "image.end(): " << image.end() << endl;
        cout << "This unlocks range iteration in for loops" << endl;
        int i = 0;
        for (auto c : image) { i++; }
        cout << "completed: " << i << " range iteration loops" << endl << endl;

        int y = 5;
        int x = 42;
        Color* row_ptr = image.rowPtr(y);
        cout << "Now we support pointer and iterator access for a given row (y)" << endl;
        cout << "image.rowPtr(y): " << row_ptr << endl;
        RowIterator r = image.row(y);
        cout << "image.row(y).data(): " << r.data() << endl;
        cout << "image.row(y).begin(): " << r.begin() << endl;
        cout << "image.row(y).end(): " << r.end() << endl;
        cout << "image.row(y)[x]: " << r[x] << endl;
        cout << "This unlocks range iteratrion in for loops with row" << endl;
        i = 0;
        for (auto r2 : image.row(y)) { i++; }
        cout << "completed: " << i << " range iteration loops over row" << endl;
        cout << "This also unlocks fill using chain from iterator" << endl;
        Color test_color(0, 255, 255);
        image.row(y).fill(test_color);
        cout << "Post fill, accessing first k elements in row: " << endl;
        for (int k = 0; k < 3; k++) { cout << r[k] << ", "; }
        cout << endl << endl;


        cout << "Now supporting region row iteration" << endl;
        RegionRowIterator rr = image.regionRows(Point(200, 100), 50, 75);
        cout << "This unlocks range iteration where rows are the sentinel" << endl;
        int filled_elements = 0;
        int filled_rows = 0;
        for (auto row : rr) { 
            row.fill(Color(69, 42, 21)); 
            filled_elements += row.size();
            filled_rows++;
        }
        cout << "filled: " << filled_elements << " elements using region row iterator" << endl;
        cout << "filled: " << filled_rows << " rows using region row iterator" << endl;
        cout << "printing 3x3 elements in tl corner: " << endl;
        RegionRowIterator debug = image.regionRows(Point(200, 100), 50, 75);
        for (int k = 0; k < 3; k++) { 
            RowIterator row = debug.row();
            for (int l = 0; l < 3; l++) { 
                cout << row[l] << ", ";
            }
            cout << endl;
            ++debug;
        }
        // does the above logic call for a region iterator? 
        cout << "This also greatly simplifies reading the region" << endl;
        int sum = 0;
        for (auto row : rr) { 
            for (auto c : row) {
                sum += c.r + c.g + c.b;
            }
        }
        cout << "sum of region: " << sum << endl << endl;

        string save_path = save_dir + "iterator_test.jpg";
        image::io::saveImageFileSystem(image, save_path);


    }

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
                int num_iterations = 10;
                for (int i = 0; i < num_iterations; i++) {
                    result = runGrid(image);
                }
                
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