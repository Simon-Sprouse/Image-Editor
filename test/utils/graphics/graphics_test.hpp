#pragma once

#include "../../base_test.hpp"
#include "../../../src/data/image/image.hpp"

#include "../../../src/utils/graphics/graphics.hpp"
#include "../../../src/data/image/io.hpp"
#include "../../../src/utils/random/random.hpp"

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


namespace Graphics::test { 

    class GraphicsTest : public ::test::BaseTest {

        public: 

            explicit GraphicsTest(const string& image_path): image_path_(image_path) {};
            
            void testLine();
            void testLineMultiple();
            void testArrow();
            void testFillPolygon();
            void testDrawSquare();
            void testDrawSquareMultiple();
            void testRandom(); // I know this is not the random test library but for now

        
            
            void runAllTests() override;




        private: 


            bool verbose_;
            string image_path_; 


           
    };

    





}