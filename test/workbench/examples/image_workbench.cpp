#include "image_workbench.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


using namespace logger;
using namespace image;

using namespace std;

#include <opencv2/opencv.hpp>


namespace workbench { 

    void runPixelConversion(string image_path, Logger logger) { 



    
        // Create Images for testing
        int rgb_linear_size = 256 * 256 * 256;
        Image<RGBA> rgb = Image<RGBA>(rgb_linear_size, 1); // size all in one row

        // todo permutation library
        int rgb_index = 0;
        for (int r = 0; r < 256; r++) { 
            for (int g = 0; g < 256; g++) { 
                for (int b = 0; b < 256; b++) { 
                    rgb.setPixel(rgb_index, RGBA(r, g, b));
                    rgb_index++;
                }
            }
        }


        // OpenCV as gt for testing
        cv::Mat rgb_mat_temp = io::imageToCvMat(rgb);
        cv::Mat hsv_mat = cv::Mat(rgb_mat_temp.size(), CV_8UC3);
        cv::cvtColor(rgb_mat_temp, hsv_mat, cv::COLOR_BGR2HSV);

        Image<HSV> hsv_dest_base = toHSV(rgb); // todo higher order call
        hsvImageCorrectnessTest(hsv_dest_base, hsv_mat);

        Image<HSV> hsv_dest_simd = toHSV_simd(rgb);
        hsvImageCorrectnessTest(hsv_dest_simd, hsv_mat);




        
        int hsv_linear_size = 1536 * 256 * 256;
        Image<HSV> hsv = Image<HSV>(hsv_linear_size, 1);
        for (int h = 0; h < 1536; h++) { 
            for (int s = 0; s < 256; s++) { 
                for (int v = 0; v < 256; v++) { 

                }
            }
        }

        cv::Mat hsv_mat_temp = io::imageToCvMat(hsv);
        cv::Mat rgb_mat = cv::Mat(hsv_mat_temp.size(), CV_8UC3);
        cv::cvtColor(hsv_mat_temp, rgb_mat, cv::COLOR_HSV2RGB);

        Image<RGBA> rgb_dest_base = toRGBA(hsv);
        rgbImageCorrectnessTest(rgb_dest_base, rgb_mat);

        Image<RGBA> rgb_dest_simd = toRGBA(hsv);
        rgbImageCorrectnessTest(rgb_dest_simd, rgb_mat);






    }







    bool hsvPixelCorrectnessTest(const HSV& test, const cv::Vec3b& gt) { 

        float test_h_normal = static_cast<float>(test.h) / 1535.0f;
        float test_s_normal = static_cast<float>(test.s) / 255.0f;
        float test_v_normal = static_cast<float>(test.v) / 255.0f;

        float cv_h_normal = static_cast<float>(gt[0]) / 180.0f;
        float cv_s_normal = static_cast<float>(gt[1]) / 255.0f;
        float cv_v_normal = static_cast<float>(gt[2]) / 255.0f;

        float h_diff = std::abs<float>(test_h_normal - cv_h_normal);
        h_diff = std::min(h_diff, 1.0f - h_diff); // handle potential wrap around
        float s_diff = std::abs<float>(test_s_normal - cv_s_normal);
        float v_diff = std::abs<float>(test_v_normal - cv_v_normal);

        float tolerance = 0.02f; // 2%

        bool test_h = h_diff <= tolerance;
        bool test_s = s_diff <= tolerance;
        bool test_v = v_diff <= tolerance;

        // handle grayscale edge cases
        if (test.s == 0) { 
            test_h = true; // hue is arbitrary in grayscale space
            return true;
        }

        bool isValid = (test_h && test_s && test_v);

        // if (!isValid) { 
        //     cout << "assertion failure hsv correctness" << endl;
        //     cout << "expected: " 
        //     << static_cast<int>(cv_h_normal*1535) << ", " 
        //     << static_cast<int>(cv_s_normal*255) << ", "
        //     << static_cast<int>(cv_v_normal*255) << endl;
        //     cout << "got: " << test << endl;
        // }

        return isValid;

    }




    bool hsvImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt) { 

        // OpenCV's fault I loop so poorly here
        int sum_passing = 0;

        for (int y = 0; y < test.getHeight(); y++) { 
            for (int x = 0; x < test.getWidth(); x++) { 
                bool isValid = hsvPixelCorrectnessTest(test.at(x, y), gt.at<cv::Vec3b>(y, x));
                if (isValid) sum_passing++;
                // if (!isValid) { 
                //     cout << "assertion failed at x, y : " << x << ", " << y << endl;
                // }
                // assert(isValid); // todo assertions are probably bad given cleanup requirements
                
            }
        }

        double percentage = static_cast<double>(sum_passing)*100 / test.linearSize();
        cout << "total passing: " << percentage << "% (" << sum_passing << " of " << test.linearSize() << ")"  << endl;


        return true;

    }




    bool rgbPixelCorrectnessTest(const RGBA& test, const cv::Vec3b gt) { 
        float test_r_normal = static_cast<float>(test.r) / 255.0f;
        float test_g_normal = static_cast<float>(test.g) / 255.0f;
        float test_b_normal = static_cast<float>(test.b) / 255.0f;

        float cv_r_normal = static_cast<float>(gt[0]) / 255.0f;
        float cv_g_normal = static_cast<float>(gt[1]) / 255.0f;
        float cv_b_normal = static_cast<float>(gt[2]) / 255.0f;

        float r_diff = std::abs<float>(test_r_normal - cv_r_normal);
        float g_diff = std::abs<float>(test_g_normal - cv_g_normal);
        float b_diff = std::abs<float>(test_b_normal - cv_b_normal);

        float tolerance = 0.02f; // todo pass or global

        bool isValid = (r_diff < tolerance) && (g_diff < tolerance) && (b_diff < tolerance);

        if (!isValid) { 
            cout << "Assertion failure: " << endl;
        }

        return isValid;

    }


    bool rgbImageCorrectnessTest(const Image<RGBA>& test, const cv::Mat& gt) { 


        int sum_passing = 0;

        for (int y = 0; y < test.getHeight(); y++) { 
            for (int x = 0; x < test.getWidth(); x++) { 
                bool isValid = rgbPixelCorrectnessTest(test.at(x, y), gt.at<cv::Vec3b>(y, x));
                if (isValid) sum_passing++;
            }
        }

        double percentage = static_cast<double>(sum_passing)*100 / test.linearSize();
        cout << "total passing: " << percentage << "% (" << sum_passing << " of " << test.linearSize() << ")"  << endl;

        return true;

    }












    void runImageConversion(string image_path, Logger logger) { 


        // todo: can logger divert cout? 
       



        int num_iterations = 1;


        // Set up Images before tests
        Image<RGBA> original = io::loadImageFileSystem(image_path);
        Image<RGBA> rgba = original.clone();
        Image<HSV> hsv = toHSV(original);


        // Set up cv::Mat before tests
        cv::setNumThreads(1);
        cout << "cv num threads: " << cv::getNumThreads() << endl << endl;

        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat rgb_mat(original_mat.size(), CV_8UC3);
        cv::Mat hsv_mat(original_mat.size(), CV_8UC3);
        cv::cvtColor(original_mat, rgb_mat, cv::COLOR_BGR2RGB);
        cv::cvtColor(rgb_mat, hsv_mat, cv::COLOR_RGB2HSV);

        
        // test names
        string suffix = std::to_string(num_iterations);
        string base_2_hsv_test = "base - rgb->hsv x " + suffix;
        string base_2_rgb_test = "base - hsv->rgb x " + suffix;
        string simd_2_hsv_test = "SIMD - rgb->hsv x " + suffix;
        string simd_2_rgb_test = "SIMD - hsv->rgb x " + suffix;
        string cv_2_hsv_test = "cv   - rgb->hsv x " + suffix;
        string cv_2_rgb_test = "cv   - hsv->rgb x " + suffix;



        // ----------------------------
        //   RGB -> HSV CONVERSIONS
        // ----------------------------

        // Base
        logger.start(base_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            hsv = toHSV(original);
        }
        logger.stop(base_2_hsv_test);
        hsvImageCorrectnessTest(hsv, hsv_mat);

        // SIMD
        logger.start(simd_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) { 
            hsv = toHSV_simd(original);
        }
        logger.stop(simd_2_hsv_test, toRGBA(hsv));
        hsvImageCorrectnessTest(hsv, hsv_mat);

        // OpenCV
        logger.start(cv_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(original_mat, hsv_mat, cv::COLOR_RGB2HSV);
        }
        logger.stop(cv_2_hsv_test);


        // ----------------------------
        //   HSV -> RGB CONVERSIONS
        // ----------------------------

        // Base
        logger.start(base_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            rgba = toRGBA(hsv);
        }
        logger.stop(base_2_rgb_test);
        rgbImageCorrectnessTest(rgba, rgb_mat);

        // SIMD
        logger.start(simd_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) { 
            rgba = toRGBA_simd(hsv);
        }
        logger.stop(simd_2_rgb_test, rgba);
        rgbImageCorrectnessTest(rgba, rgb_mat);

        // OpenCV
        logger.start(cv_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(hsv_mat, rgb_mat, cv::COLOR_HSV2RGB);
        }
        logger.stop(cv_2_rgb_test);


        



    }



}