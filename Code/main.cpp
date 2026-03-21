#include <iostream>
#include <chrono>
#include <cmath>
#include <string>


#include "../Test/Utils/ImageProcess/ImageProcessTest.hpp"
#include "../Test/Utils/Geometry/geometryTest.hpp"
#include "../Test/Utils/Graphics/graphicsTest.hpp"
#include "../Test/Routines/Mosaic/MosaicTest.hpp"

#include "App/run_Mosaic.hpp"



int main() { 

    using namespace std;
    using image::Image;
    using mosaic_gen::Mosaic;


    string file_system_image_path = "../Images/flower.jpg";
    string file_system_save_dir = "../Results/";




    // mosaic_gen::test::MosaicTest my_mosaic_test(params, file_system_image_path, file_system_save_dir);
    // my_mosaic_test.runAllTests();








   
    auto start = std::chrono::high_resolution_clock::now();


    app::runMosaic(file_system_image_path, file_system_save_dir);

   


    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Main.cpp execution time: " << elapsed.count() << " s" << endl;






    return 0;
}


