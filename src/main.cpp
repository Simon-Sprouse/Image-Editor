#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "../test/routines/mosaic/mosaic_test.hpp"

#include "app/run_mosaic.hpp"



int main() { 

    using namespace std;
    using image::Image;
    using mosaic_gen::Mosaic;


    string file_system_image_path = "../images/flower.jpg";
    string file_system_save_dir = "../results/";




    // mosaic_gen::test::MosaicTest my_mosaic_test(params, file_system_image_path, file_system_save_dir);
    // my_mosaic_test.runAllTests();








   
    auto start = std::chrono::high_resolution_clock::now();


    app::runMosaic(file_system_image_path, file_system_save_dir);

   


    


    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Main.cpp execution time: " << elapsed.count() << " s" << endl;






    return 0;
}


