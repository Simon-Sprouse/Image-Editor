#pragma once

#include "../../base_test.hpp"
#include "../../../src/data/image/image.hpp"

#include "../../../src/data/image/io.hpp"
#include "../../../src/utils/image_process/imageProcess.hpp"

namespace image::process::test { 


    class ProcessTest : public ::test::BaseTest { 


        public: 

            explicit ProcessTest(const string& image_path): image_path_(image_path) {};

            void testLoadImage();
//             void squeebTest();
//             void testResize();
//             void testGrayscale();
//             void testBlur();
//             void testSobel();
//             void testCanny();
//             void testContours();

            void testComputeDistanceField(); // TODO needs visualization, maybe image constructor from float vector
            void testDistanceGradients();
            void testVectorField();

            

        
            
            void runAllTests() override;




        private: 



            string image_path_; 












    };






}