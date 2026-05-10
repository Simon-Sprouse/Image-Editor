#include "image_workbench.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include <iostream>
#include <vector>


using namespace logger;
using namespace image;

using namespace std;

#include <opencv2/opencv.hpp>


namespace workbench { 

    void runPrimitives(string image_path, Logger logger) { 


        logger.start("constructors");
        {
            image::RGBA rgba(0);

            image::HSV a(0);
            cout << a << endl;

            image::HSV b(1000, 20, 20);
            cout << b << endl;

            image::GRAY c(240);
            cout << c << endl;
        
        }
        logger.stop("constructors"); // todo make these legit



        logger.start("conversions");
        {

            RGBA rgba(210, 42, 69);
            HSV hsv(1234, 73, 21);
            GRAY gray(93);

            cout << "RGBA: " << rgba << endl;
            cout << "RGBA.toGRAY(): " << rgba.toGray() << endl;
            // cout << "RGBA.toHSV(): " << rgba.toHSV() << endl;



            HSV test = RGBA2HSV(rgba);
            cout << "HSV: " << test << endl;


        }
        logger.stop("conversions");







        Image<RGBA> original = io::loadImageFileSystem(image_path);
        Image<HSV> hsv(original.size());

        logger.start("hsv image conversion X 100");
        {
            int num_iterations = 100;
            for (int i = 0; i < num_iterations; i++) {
                for (int j = 0; j < original.linearSize(); j++) { 
                    hsv.setPixel(j, RGBA2HSV(original.at(j)));
                }
            }
            cout << "sum_iterations: " << original.linearSize() * num_iterations << endl;
        }
        logger.stop("hsv image conversion X 100");






        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat hsv_mat = cv::Mat(original_mat.size(), CV_8UC3);

        cv::Vec4b rgb_pixel;
        cv::Vec3b hsv_pixel;

        // used for passing to cvtColor
        cv::Mat src_px = cv::Mat(1, 1, CV_8UC4, &rgb_pixel);
        cv::Mat dst_px = cv::Mat(1, 1, CV_8UC3, &hsv_pixel);

        cv::Vec4b* src_ptr = original_mat.ptr<cv::Vec4b>();
        cv::Vec3b* dst_ptr = hsv_mat.ptr<cv::Vec3b>();
        logger.start("cv hsv image conversion x 100");
        {
            int num_iterations = 100;
            for (int i = 0; i < num_iterations; i++) {
                for (int j = 0; j < original_mat.total(); j++) { 
                    rgb_pixel = src_ptr[j];
                    cv::cvtColor(src_px, dst_px, cv::COLOR_RGB2HSV);
                    dst_ptr[j] = hsv_pixel;
                }
            }
            cout << "sum_iterations: " << num_iterations * original_mat.total() << endl;
        }
        logger.stop("cv hsv image conversion x 100");




    }













    void runImage(string image_path, Logger logger) { 



        Image<RGBA> original = io::loadImageFileSystem(image_path);
        


        // todo multi hsv to rgb convert


      


        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat hsv_mat = cv::Mat(original_mat.size(), CV_8UC4);
        logger.start("cv hsv image conversion x 100");
        {
            int num_iterations = 100;
            for (int i = 0; i < num_iterations; i++) {
                cv::cvtColor(original_mat, hsv_mat, cv::COLOR_RGB2HSV);
            }
            cout << "sum_iterations: " << num_iterations * original_mat.total() << endl;
        }
        logger.stop("cv hsv image conversion x 100");




       










    }
}