#pragma once

#include "../../base_test.hpp"

#include "../../../src/utils/geometry/geometry.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include "../../../src/utils/random/random.hpp"

#include <string>
#include <iostream>
#include <iomanip>

#include <opencv2/opencv.hpp>

using namespace std;


namespace Geometry::test { 

    class GeometryTest : public ::test::BaseTest {

        public: 

            explicit GeometryTest(const string& image_path): image_path_(image_path) {};
            // TODO dynamically set verbosity
            // GeometryTest(const string& image_path, bool verbose) : image_path_(image_path), verbose_(verbose) {};

            bool testComputeMean();
            bool testCovarianceMatrix();
            bool testFirstEigenVector();
            bool testPcaLength();
            bool testPcaDirection();

        
            
            void runAllTests() override;




        private: 


            bool verbose_;
            string image_path_; 


           
    };

    





}