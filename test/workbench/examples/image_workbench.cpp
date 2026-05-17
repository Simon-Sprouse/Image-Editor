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

    void runPrimitives(string image_path, Logger logger) { 


        // logger.start("constructors");
        // {
        //     image::RGBA rgba(0);

        //     image::HSV a(0);
        //     cout << a << endl;

        //     image::HSV b(1000, 20, 20);
        //     cout << b << endl;

        //     image::GRAY c(240);
        //     cout << c << endl;
        
        // }
        // logger.stop("constructors"); // todo make these legit



        // logger.start("conversions");
        // {

        //     RGBA rgba(210, 42, 69);
        //     HSV hsv(1234, 73, 21);
        //     GRAY gray(93);

        //     cout << "RGBA: " << rgba << endl;
        //     cout << "RGBA.toGRAY(): " << rgba.toGray() << endl;
        //     // cout << "RGBA.toHSV(): " << rgba.toHSV() << endl;



        //     HSV test = RGBA2HSV(rgba);
        //     cout << "HSV: " << test << endl;


        // }
        // logger.stop("conversions");







        Image<RGBA> original = io::loadImageFileSystem(image_path);
        Image<HSV> hsv(original.size());
        for (int j = 0; j < original.linearSize(); j++) { 
            hsv.setPixel(j, RGBA2HSV(original.at(j)));
        }





        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat hsv_mat = cv::Mat(original_mat.size(), CV_8UC3);

        cv::Vec4b rgb_pixel;
        cv::Vec3b hsv_pixel;

        // used for passing to cvtColor
        cv::Mat src_px = cv::Mat(1, 1, CV_8UC4, &rgb_pixel);
        cv::Mat dst_px = cv::Mat(1, 1, CV_8UC3, &hsv_pixel);

        cv::Vec4b* src_ptr = original_mat.ptr<cv::Vec4b>();
        cv::Vec3b* dst_ptr = hsv_mat.ptr<cv::Vec3b>();
        // logger.start("cv hsv image conversion x 100");
        // {
        //     int num_iterations = 100;
        //     for (int i = 0; i < num_iterations; i++) {
        //         for (int j = 0; j < original_mat.total(); j++) { 
        //             rgb_pixel = src_ptr[j];
        //             cv::cvtColor(src_px, dst_px, cv::COLOR_RGB2HSV);
        //             dst_ptr[j] = hsv_pixel;
        //         }
        //     }
        //     cout << "sum_iterations: " << num_iterations * original_mat.total() << endl;
        // }
        // logger.stop("cv hsv image conversion x 100");




        cv::Mat rgb_mat(original_mat.size(), CV_8UC3);
        cv::cvtColor(original_mat, rgb_mat, cv::COLOR_BGR2RGB);
        logger.start("hsv conversion correctness test");
        {
            // gt 
            cv::cvtColor(rgb_mat, hsv_mat, cv::COLOR_RGB2HSV);

            // create test array for our conversion
            for (int j = 0; j < original.linearSize(); j++) { 
                hsv.setPixel(j, RGBA2HSV(original.at(j)));
            }

            // check test array against gt
            for (int i = 0; i < hsv.linearSize(); i++) { 

                RGBA my_rgb = original.at(i);
                HSV my_hsv = hsv.at(i);
                float my_normalized_hue = static_cast<float>(my_hsv.h) / 1535.0f;

                cv::Vec3b cv_rgb = rgb_mat.ptr<cv::Vec3b>()[i];
                cv::Vec3b cv_hsv = hsv_mat.ptr<cv::Vec3b>()[i];
                float cv_normalized_hue = static_cast<float>(cv_hsv[0]) / 180.0f;

                float diff = std::abs<float>((my_normalized_hue - cv_normalized_hue));
                diff = std::min(diff, 1.0f - diff);

                // todo static assert would be bad here right? 
                assert(diff <= 0.021);

                // cout << "i: " << i << endl;
                // cout << "rgb_image.at(" << i << "): " << my_rgb << endl;
                // cout << "rgb_mat.at(" << i << "): " << cv_rgb << endl;
                // cout << "hsv.at(" << i << "): " << my_hsv << endl;
                // cout << "hsv_mat.at(" << i << "): " << cv_hsv << endl;
                // cout << "my normal hue: " << my_normalized_hue << endl;
                // cout << "cv normal hue: " << cv_normalized_hue << endl;
                // cout << "diff: " << diff << endl;
                // cout << endl;
            }




            for (int r = 0; r < 256; r++) { 
                for (int g = 0; g < 256; g++) { 
                    for (int b = 0; b < 256; b++) { 
                        RGBA(r, g, b).toHsv();
                    }
                }
            }
            

        }
        logger.stop("hsv conversion correctness test");


        // todo display messed up hsv image at some point



        
        logger.start("rgb conversion correctness test");
        { 
            for (auto px : original) {

                HSV hsv = RGBA2HSV(px);
                RGBA rgba = HSV2RGBA(hsv);

                // todo this tolerance is too high, conversion bug likely exists
                assert(px - rgba < RGBA(4));
                // cout << "px - rgba: " << px - rgba << endl;
                // cout << "(px - rgba) < RGBA(1): " << ((px - rgba) < RGBA(1)) << endl;
                

                // cout << "original: " << px << endl;
                // cout << "hsv: " << hsv << endl;
                // cout << "rgba: " << rgba << endl;
                // cout << endl;

            }


            for (int h = 0; h < 1536; h++) { 
                for (int s = 0; s < 256; s++) { 
                    for (int v = 0; v < 256; v++) { 
                        HSV(h, s, v).toRgba();
                    }
                }
            }




            
        }
        logger.stop("rgb conversion correctness test");














    }













    void runImage(string image_path, Logger logger) { 


        Image<RGBA> original = io::loadImageFileSystem(image_path);
        logger.start("Image Converison Correctness Test");
        {
            Image<HSV> hsv = toHSV(original);
            Image<RGBA> rgba = toRGBA(hsv);

            // todo: overload subtraction and lt on image class
            for (int i = 0; i < original.linearSize(); i++) {
                // assert((int)(original.at(i) - rgba.at(i) < RGBA(3)));

                if (!((int)(original.at(i) - rgba.at(i) < RGBA(4)))) { 
                    cout << "assertion faliure: " << endl; 
                    cout << "i: " << i << endl;
                    cout << "original.at(i): " << original.at(i) << endl;
                    cout << "rgba.at(i): " << rgba.at(i) << endl;
                    cout << "original.at(i) - rgba.at(i): " << original.at(i) - rgba.at(i) << endl;
                    cout << "RGBA(4): " << RGBA(4) << endl;
                    cout << "original.at(i) - rgba.at(i) < RGBA(3): " << (int)(original.at(i) - rgba.at(i) < RGBA(3)) << endl;
                    cout << endl;
                }


                
            }
        }
        logger.stop("Image Converison Correctness Test");













        int num_iterations = 100;

    
        Image<HSV> hsv = Image<HSV>(original.size());
        Image<RGBA> rgba = Image<RGBA>(original.size());


        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat hsv_mat = cv::Mat(original_mat.size(), CV_8UC4);
        cv::Mat rgb_mat = cv::Mat(original_mat.size(), CV_8UC4);
        cv::setNumThreads(1);
        cout << "cv num threads: " << cv::getNumThreads() << endl << endl;

        // test names
        string suffix = std::to_string(num_iterations);
        string im_rgb_hsv_test = "im rgb->hsv x " + suffix;
        string im_hsv_rgb_test = "im hsv->rgb x " + suffix;
        string cv_rgb_hsv_test = "cv rgb->hsv x " + suffix;
        string cv_hsv_rgb_test = "cv hsv->rgb x " + suffix;


        


        // Test our Image RGB -> HSV
        logger.start(im_rgb_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            // for (int j = 0; j < original.linearSize(); j++) { 
            //     hsv.setPixel(j, RGBA2HSV(original.at(j)));
            // }
            toHSV(original);
        }
        logger.stop(im_rgb_hsv_test);


        // Test our Image HSV -> RGB
        logger.start(im_hsv_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            // for (int j = 0; j < hsv.linearSize(); j++) { 
                // rgba.setPixel(j, HSV2RGBA(hsv.at(j)));
                toRGBA(hsv);
            // }
        }
        logger.stop(im_hsv_rgb_test);


        // Test OpenCV CovtColor RGB -> HSV
        logger.start(cv_rgb_hsv_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(original_mat, hsv_mat, cv::COLOR_RGB2HSV);
        }
        logger.stop(cv_rgb_hsv_test);



        // Test OpenCV CovtColor HSV -> RGB
        logger.start(cv_hsv_rgb_test);
        for (int i = 0; i < num_iterations; i++) {
            cv::cvtColor(hsv_mat, rgb_mat, cv::COLOR_HSV2RGB);
        }
        logger.stop(cv_hsv_rgb_test);



       



        



       










    }



    // todo unused so far 
    bool hsvImageCorrectnessTest(const Image<HSV>& test, const cv::Mat& gt) { 


        for (int i = 0; i < test.linearSize(); i++) { 

            float test_h_normal = static_cast<float>(test.at(i).h) / 1535.0f;
            float test_s_normal = static_cast<float>(test.at(i).s) / 255.0f;
            float test_v_normal = static_cast<float>(test.at(i).v) / 255.0f;

            cv::Vec3b cv_ptr = gt.ptr<cv::Vec3b>()[i];
            float cv_h_normal = static_cast<float>(cv_ptr[0]) / 180.0f;
            float cv_s_normal = static_cast<float>(cv_ptr[1]) / 255.0f;
            float cv_v_normal = static_cast<float>(cv_ptr[2]) / 255.0f;

            float h_diff = std::abs<float>(test_h_normal - cv_h_normal);
            h_diff = std::min(h_diff, 1.0f - h_diff); // handle potential wrap around
            float s_diff = std::abs<float>(test_s_normal - cv_s_normal);
            float v_diff = std::abs<float>(test_v_normal - cv_v_normal);

            float tolerance = 0.02f;

            assert(h_diff <= tolerance);
            assert(s_diff <= tolerance);
            assert(v_diff <= tolerance);

        }

        return true;


    }







    bool rgbImageCorrectnessTest(const Image<RGBA>& test, const cv::Mat& gt) { 


        for (int i = 0; i < test.linearSize(); i++) { 

            float test_r_normal = static_cast<float>(test.at(i).r) / 255.0f;
            float test_g_normal = static_cast<float>(test.at(i).g) / 255.0f;
            float test_b_normal = static_cast<float>(test.at(i).b) / 255.0f;

            cv::Vec3b cv_ptr = gt.ptr<cv::Vec3b>()[i];
            float cv_r_normal = static_cast<float>(cv_ptr[0]) / 255.0f;
            float cv_g_normal = static_cast<float>(cv_ptr[1]) / 255.0f;
            float cv_b_normal = static_cast<float>(cv_ptr[2]) / 255.0f;

            float r_diff = std::abs<float>(test_r_normal - cv_r_normal);
            float g_diff = std::abs<float>(test_g_normal - cv_g_normal);
            float b_diff = std::abs<float>(test_b_normal - cv_b_normal);

            float tolerance = 0.02f;

            if (!(r_diff <= tolerance)) {
                cout << "r_diff asertion failed: " << r_diff << endl;
            }
            if (!(g_diff <= tolerance)) {
                cout << "g_diff asertion failed: " << g_diff << endl;
            }
            if (!(b_diff <= tolerance)) {
                cout << "b_diff asertion failed: " << b_diff << endl;
            }

            if (!(r_diff <= tolerance) || !(g_diff <= tolerance) || !(b_diff <= tolerance)) { 
                cout << "index: " << i << endl;
                cout << "rgba from test: " << test.at(i) << endl;
                cout << "rgb from cv: " << (int)cv_ptr[0] << ", " << (int)cv_ptr[1] << ", " << (int)cv_ptr[2] << endl;
            }
            

            assert(r_diff <= tolerance);
            assert(g_diff <= tolerance);
            assert(b_diff <= tolerance);

        }

        return true;


    }












    void runImageSIMD(string image_path, Logger logger) { 



        Image<RGBA> original = io::loadImageFileSystem(image_path);
        Image<RGBA> rgba = original.clone();
        Image<HSV> hsv = toHSV(original);


        cout << "original size: " << original.size() << endl;
        cout << "original linear size: " << original.linearSize() << endl;

        // for testing
        cv::Mat original_mat = io::imageToCvMat(original);
        cv::Mat rgb_mat(original_mat.size(), CV_8UC3);
        cv::Mat hsv_mat(original_mat.size(), CV_8UC3);
        cv::cvtColor(original_mat, rgb_mat, cv::COLOR_BGR2RGB);
        cv::cvtColor(rgb_mat, hsv_mat, cv::COLOR_RGB2HSV);


        logger.start("simd test");
        HSV* hsv_ptr = hsv.data();
        RGBA* rgba_ptr = rgba.data();
        HSV2RGBA_simd(hsv_ptr, rgba_ptr);


        // hsv 2 is dest for new rgb -> hsv test
        Image<HSV> hsv_2 = Image<HSV>(original.size());
        Image<RGBA> rgba_2 = original.clone();
        HSV* hsv_ptr_2 = hsv_2.data();
        RGBA* rgba_ptr_2 = rgba_2.data();
        RGBA2HSV_simd(rgba_ptr_2, hsv_ptr_2);




        for (int i = 0; i < 16; i++) { 

            HSV gt = rgba_ptr_2[i].toHsv();

            cout << "i: " << i << endl;
            cout << "rgba_ptr[i]: " << rgba_ptr_2[i] << endl;
            cout << "hsv_ptr[i]: " << hsv_ptr_2[i] << endl;
            cout << "expected: " << gt << endl;
            cout << endl;
        }






        // cout << "hsv_ptr: " << hsv_ptr << endl;
        // cout << "*hsv_ptr: " << *hsv_ptr << endl;
        // cout << endl;


        // for (int i = 0; i < 16; i++) { 
        //     cout << "i: " << i << endl;
        //     cout << "hsv_ptr + i: " << hsv_ptr + i << endl;
        //     cout << "hsv_ptr[i]" << hsv_ptr[i] << endl;
        //     cout << endl;
        // }



        // cout << "rgba_ptr: " << rgba_ptr << endl;
        // cout << "*rgba_ptr: " << *rgba_ptr << endl;
        // cout << endl;


        // for (int i = 0; i < 16; i++) { 
        //     cout << "i: " << i << endl;
        //     cout << "rgba_ptr + i: " << rgba_ptr + i << endl;
        //     cout << "rgba_ptr[i]" << rgba_ptr[i] << endl;
        //     cout << endl;
        // }






        logger.stop("simd test");



        int num_iterations = 100;
        logger.start("naive conversion");
        for (int i = 0; i < num_iterations; i++) {
            rgba = toRGBA(hsv);
        }
        logger.stop("naive conversion");

        logger.start("simd conversion");
        for (int i = 0; i < num_iterations; i++) {
            rgba = toRGBA_simd(hsv);
        }
        logger.stop("simd conversion", rgba);




        logger.start("new correctness test");
        rgbImageCorrectnessTest(rgba, rgb_mat);
        // hsvImageCorrectnessTest(hsv, hsv_mat);
        logger.stop("new correctness test");


        



    }


   

















}