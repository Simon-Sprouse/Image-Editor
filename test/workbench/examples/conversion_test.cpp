#include "conversion_test.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/primitives.hpp"
#include "../../../src/data/image/pixel.hpp"
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




    void conversionUsage(string image_path, Logger logger) { 


        // ----------------
        // FREE functions

        // free functions scalar
        // names are esoteric on purpose. these are helpers for .to<Px>()
        // RGB2HSV(const RGB& px)
        // RGB2GRAY(const RGB& px)
        // HSV2RGB(const HSV& px)

        // free functions vector
        // RGB2HSV_simd(RGB* src, HSV* dest)
        // HSV2RBG_simd(HSV* src, RGB* src)
        

        // ----------------------------------
        // STRUCT owned conversion functions
        // need to make these nodiscard

        // rgb.to<HSV>()
        // rgb.to<GRAY>()
        // hsv.to<RGB>()

        // -----------------------------------
        // IMAGE owned conversion functions
        // also need to make these nodiscard

        // rgb_img.to<HSV>() 
        // rgb_img.to<GRAY>()
        // hsv_img.to<RGB>()

        // rgb_img.to_simd<HSV>() // add into to function with branching
        // hsv_img.to_simd<RGB>()


        cout << endl;
        cout << "Hello from Usage test" << endl << endl;

        const Image<RGB> original = io::loadImageFileSystem(image_path);


        // Scalar functions
        cout << "--------------" << endl;
        cout << "Free functions: 1a Scalar Pixel" << endl << endl;

        // RGB2HSV() RGB2GRAY()
        {
            RGB rgb_px = RGB(42, 69, 210);
            HSV rgb_px_2_hsv_px = RGB2HSV(rgb_px);
            GRAY rgb_px_2_gray_px = RGB2GRAY(rgb_px);
            cout << "rgb_px: " << rgb_px << endl;
            cout << "to hsv px: " << rgb_px_2_hsv_px << endl;
            cout << "to gray px: " << rgb_px_2_gray_px << endl;
            cout << endl;
        }

        // HSV2RGB()
        {
            HSV hsv_px = HSV(1224, 255, 100);
            RGB hsv_px_2_rgb_px = HSV2RGB(hsv_px);
            cout << "hsv_px: " << hsv_px << endl;
            cout << "to rgb_px: " << hsv_px_2_rgb_px << endl;
            cout << endl;
        }


        // Vector functions
        cout << "--------------" << endl;
        cout << "Free functions: 1b Vector Pixel" << endl << endl;

        // RGB2HSV_simd()
        {
            const RGB* rgb_ptr = original.data(); // todo make this .ptr()
            Image<HSV> hsv_img_buf = Image<HSV>(original.size()); // todo original.copySize();
            HSV* hsv_ptr = hsv_img_buf.data();
            RGB2HSV_simd(rgb_ptr, hsv_ptr);
            cout << "rgb_ptr (src): " << rgb_ptr << endl;
            cout << "hsv px (dst): " << hsv_ptr << endl;

            cout << "rgb data (src)" << endl;
            for (int i = 0; i < 16; i++) { 
                cout << rgb_ptr[i] << endl;
            }
            cout << "hsv data (cvt)" << endl;
            for (int i = 0; i < 16; i++) { 
                cout << hsv_ptr[i] << endl;
            }
            cout << endl;
        }

        // HSV2RGB_simd()
        {
            Image<HSV> hsv_img_buf = Image<HSV>(original.size()); // todo original.copySize();
            HSV* hsv_ptr = hsv_img_buf.data();
            RGB2HSV_simd(original.data(), hsv_ptr);

            Image<RGB> rgb_img_buf = Image<RGB>(original.size());
            RGB* rgb_ptr = rgb_img_buf.data();
            HSV2RGB_simd(hsv_ptr, rgb_ptr);

            cout << "hsv_ptr (src): " << hsv_ptr << endl;
            cout << "rgb px (dst): " << rgb_ptr << endl;

            cout << "hsv data (src)" << endl; // todo duplicated print functions
            for (int i = 0; i < 16; i++) { 
                cout << hsv_ptr[i] << endl;
            }
            cout << "rgb data (cvt)" << endl;
            for (int i = 0; i < 16; i++) { 
                cout << rgb_ptr[i] << endl;
            }
            cout << endl;
        }






        // Struct Owned Functions
        cout << "--------------" << endl;
        cout << "Struct Functions" << endl << endl;

        {
            RGB rgb_px = RGB(42, 69, 210);
            HSV rgb_px_2_hsv_px = rgb_px.to<HSV>();
            GRAY rgb_px_2_gray_px = rgb_px.to<GRAY>();
            cout << "rgb_px: " << rgb_px << endl;
            cout << "to hsv px: " << rgb_px_2_hsv_px << endl;
            cout << "to gray px: " << rgb_px_2_gray_px << endl;
            cout << endl;

            HSV hsv_px = HSV(1224, 255, 100);
            RGB hsv_px_2_rgb_px = hsv_px.to<RGB>();
            // TODO: COLOR PRINTING IN TERMINAL FOR OUR COLORS!!!!
            cout << "hsv_px: " << hsv_px << endl;
            cout << "to rgb_px: " << hsv_px_2_rgb_px << endl;
            cout << endl;


            // just for fun - chaining
            GRAY rgb_px_chain = RGB(0, 100, 200).to<HSV>().to<RGB>().to<GRAY>();
            cout << "chain: " << rgb_px_chain << endl;

            cout << endl;

        }


        // Image Ownded Functions
        cout << "--------------" << endl;
        cout << "Image Functions" << endl << endl;

        {
            Image<HSV> rgb_img_2_hsv_img = original.to<HSV>();
            cout << "rgb_img.to<HSV>(): " << rgb_img_2_hsv_img << endl;
            cout << ".at(0): " << rgb_img_2_hsv_img.at(0) << endl;

            Image<GRAY> rgb_img_2_gray_img = original.to<GRAY>();
            cout << "rgb_img.to<GRAY>(): " << rgb_img_2_gray_img << endl;
            cout << ".at(0): " << rgb_img_2_gray_img.at(0) << endl;

            Image<HSV> hsv_img = original.to<HSV>();
            Image<RGB> hsv_img_2_rgb_img = hsv_img.to<RGB>(); 
            cout << "hsv_img.to<RGB>(): " << hsv_img_2_rgb_img << endl;
            cout << ".at(0): " << hsv_img_2_rgb_img.at(0) << endl;
        }
















        

        cout << endl;
    }



    // Test all possilble pixel combinations
    void conversionUnitTest(string image_path, Logger logger) { 

        cout << "Testing all permutations for correctness" << endl;

        // set tolerance level
        float tolerance = 0.02f; // 2%

        // ----------------------------
        //   RGB -> HSV CORRECTNESS
        // ----------------------------
    
        // Create Images for testing
        int rgb_linear_size = 256 * 256 * 256;
        Image<RGB> rgb = Image<RGB>(rgb_linear_size, 1); // size all in one row

        // todo permutation library
        int rgb_index = 0;
        for (int r = 0; r < 256; r++) { 
            for (int g = 0; g < 256; g++) { 
                for (int b = 0; b < 256; b++) { 
                    rgb.setPixel(rgb_index, RGB(r, g, b));
                    rgb_index++;
                }
            }
        }

        // OpenCV as gt for testing
        cv::Mat rgb_mat_src = io::imageToCvMat(rgb);
        cv::Mat hsv_mat_gt = cv::Mat(rgb_mat_src.size(), CV_8UC3);
        cv::cvtColor(rgb_mat_src, hsv_mat_gt, cv::COLOR_BGR2HSV);

        // Test scalar conversion (NOTE - not supported as API)
        cout << "test rgb->hsv scalar" << endl;
        Image<HSV> hsv_test_scalar = Image<HSV>(rgb.size()); // todo copySize()
        for (int i = 0; i < hsv_test_scalar.linearSize(); i++) { 
            hsv_test_scalar.setPixel(i, rgb.at(i).to<HSV>());
        }
        hsvImageCorrectnessTest(hsv_test_scalar, hsv_mat_gt, tolerance);

        // Test simd conversion
        cout << "test rgb->hsv simd" << endl;
        Image<HSV> hsv_test_simd = rgb.to<HSV>();
        hsvImageCorrectnessTest(hsv_test_simd, hsv_mat_gt, tolerance);

        // todo test RGB -> GRAY

        // ----------------------------
        //   HSV -> RGB CORRECTNESS
        // ----------------------------
        
        int hsv_linear_size = 1536 * 256 * 256;
        Image<HSV> hsv = Image<HSV>(hsv_linear_size, 1);

        int hsv_index = 0;
        for (int h = 0; h < 1536; h++) { 
            for (int s = 0; s < 256; s++) { 
                for (int v = 0; v < 256; v++) { 
                    hsv.setPixel(hsv_index, HSV(h, s, v));
                    hsv_index++;
                }
            }
        }

        cv::Mat hsv_mat_src = io::imageToCvMat(hsv);
        cv::Mat rgb_mat_gt = cv::Mat(hsv_mat_src.size(), CV_8UC3);
        cv::cvtColor(hsv_mat_src, rgb_mat_gt, cv::COLOR_HSV2RGB);

        // Test Scalar conversion (NOTE - not supported as API)
        // todo, these tests are bad because of low preceision on OpenCV's part
        // the best fix is to use our already tested rgb conversion to backwards
        // compare. Ie run hsv->rgb and compare (our rgb, our rgb(from conversion))
        // run tests
        cout << "test hsv -> rgb base" << endl;
        Image<RGB> rgb_test_scalar = Image<RGB>(hsv.size());
        for (int i = 0; i < rgb_test_scalar.linearSize(); i++) { 
            rgb_test_scalar.setPixel(i, hsv.at(i).to<RGB>());
        }
        rgbImageCorrectnessTest(rgb_test_scalar, rgb_mat_gt, tolerance);

        cout << "test rgb -> hsv simd" << endl;
        Image<RGB> rgb_test_simd = hsv.to<RGB>();
        rgbImageCorrectnessTest(rgb_test_simd, rgb_mat_gt, tolerance);

        cout << endl;
    }




    void conversionBenchmark(string image_path, Logger logger) { 


        // ----------------------------
        //     PRE - TEST CONFIG
        // ----------------------------


        int num_iterations = 1;

        // Set up Images before tests
        Image<RGB> original = io::loadImageFileSystem(image_path);
        Image<RGB> rgb_src = original.clone();
        Image<HSV> hsv_src = rgb_src.to<HSV>();
        Image<RGB> rgb_dest(original.size());
        Image<HSV> hsv_dest(original.size());

        // Set cv threads to ensure fairness
        cv::setNumThreads(1);
        cout << "cv num threads: " << cv::getNumThreads() << endl;
        cout << endl;

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

        // todo: can logger divert cout? 
        cout << "Testing RGB -> HSV Conversions" << endl;

        // Base
        logger.start(base_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            for (int j = 0; j < rgb_src.linearSize(); j++) { 
                hsv_dest.setPixel(j, rgb_src.at(j).to<HSV>());
            }
        }
        logger.stop(base_2_hsv_test, hsv_dest);

        // SIMD todo - bug seems to be different visually from base
        logger.start(simd_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) { 
            hsv_dest = rgb_src.to<HSV>();
        }
        logger.stop(simd_2_hsv_test, hsv_dest);

        // OpenCV
        logger.start(cv_2_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(original_mat, hsv_mat, cv::COLOR_RGB2HSV);
        }
        logger.stop(cv_2_hsv_test);

        cout << endl;


        // ----------------------------
        //   HSV -> RGB CONVERSIONS
        // ----------------------------

        cout << "Testing HSV -> RGB Conversions" << endl;

        // Base
        logger.start(base_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            for (int j = 0; j < hsv_src.linearSize(); j++) { 
                rgb_dest.setPixel(j, hsv_src.at(j).to<RGB>());
            }
        }
        logger.stop(base_2_rgb_test, rgb_dest);

        // SIMD
        logger.start(simd_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) { 
            rgb_dest = hsv_src.to<RGB>();
        }
        logger.stop(simd_2_rgb_test, rgb_dest);

        // OpenCV
        logger.start(cv_2_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(hsv_mat, rgb_mat, cv::COLOR_HSV2RGB);
        }
        logger.stop(cv_2_rgb_test);



    }




    bool hsvPixelCorrectnessTest(const HSV& test, const cv::Vec3b& gt, float tolerance) { 

        float test_h_normal = static_cast<float>(test.h) / 1535.0f;
        float test_s_normal = static_cast<float>(test.s) / 255.0f;
        float test_v_normal = static_cast<float>(test.v) / 255.0f;

        float cv_h_normal = static_cast<float>(gt[0]) / 180.0f;
        float cv_s_normal = static_cast<float>(gt[1]) / 255.0f;
        float cv_v_normal = static_cast<float>(gt[2]) / 255.0f;

        // todo update all of this to use pixel.hpp functions
        float h_diff = std::abs<float>(test_h_normal - cv_h_normal);
        h_diff = std::min(h_diff, 1.0f - h_diff); // handle potential wrap around
        float s_diff = std::abs<float>(test_s_normal - cv_s_normal);
        float v_diff = std::abs<float>(test_v_normal - cv_v_normal);

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



    bool rgbPixelCorrectnessTest(const RGB& test, const cv::Vec3b gt, float tolerance) { 

        float test_r_normal = static_cast<float>(test.r) / 255.0f;
        float test_g_normal = static_cast<float>(test.g) / 255.0f;
        float test_b_normal = static_cast<float>(test.b) / 255.0f;

        float cv_r_normal = static_cast<float>(gt[0]) / 255.0f;
        float cv_g_normal = static_cast<float>(gt[1]) / 255.0f;
        float cv_b_normal = static_cast<float>(gt[2]) / 255.0f;

        float r_diff = std::abs<float>(test_r_normal - cv_r_normal);
        float g_diff = std::abs<float>(test_g_normal - cv_g_normal);
        float b_diff = std::abs<float>(test_b_normal - cv_b_normal);

        bool isValid = (r_diff < tolerance) && (g_diff < tolerance) && (b_diff < tolerance);

        // if (!isValid) { 
        //     cout << "assertion failure hsv correctness" << endl;
        //     cout << "expected: " 
        //     << static_cast<int>(cv_r_normal*255) << ", " 
        //     << static_cast<int>(cv_g_normal*255) << ", "
        //     << static_cast<int>(cv_b_normal*255) << endl;
        //     cout << "got: " << test << endl;
        // }

        return isValid;

    }


    bool hsvImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt, float tolerance) { 

        // OpenCV's fault I loop so poorly here
        int sum_passing = 0;

        for (int y = 0; y < test.getHeight(); y++) { 
            for (int x = 0; x < test.getWidth(); x++) { 
                bool isValid = hsvPixelCorrectnessTest(test.at(x, y), gt.at<cv::Vec3b>(y, x), tolerance);
                if (isValid) sum_passing++;
            }
        }

        double percentage = static_cast<double>(sum_passing)*100 / test.linearSize();
        cout << "total passing: " << percentage << "% (" << sum_passing << " of " << test.linearSize() << ")"  << endl;

        return true;

    }


    bool rgbImageCorrectnessTest(const Image<RGB>& test, const cv::Mat& gt, float tolerance) { 

        int sum_passing = 0;

        for (int y = 0; y < test.getHeight(); y++) { 
            for (int x = 0; x < test.getWidth(); x++) { 
                bool isValid = rgbPixelCorrectnessTest(test.at(x, y), gt.at<cv::Vec3b>(y, x), tolerance);
                if (isValid) sum_passing++;
            }
        }

        double percentage = static_cast<double>(sum_passing)*100 / test.linearSize();
        cout << "total passing: " << percentage << "% (" << sum_passing << " of " << test.linearSize() << ")"  << endl;

        return true;

    }



}