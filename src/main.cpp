#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include "../test/workbench/workbench_main.hpp"
#include "../test/unit/unit_test_main.hpp"


#include "app/app.hpp"



int main() { 

    using namespace std;



    // paths reletive to the build folder (where executable is built)
    string file_system_image_path = "../images/flower.jpg";
    string file_system_save_dir = "../results/";








   
    auto start = std::chrono::high_resolution_clock::now();






    // unit_test::runAll(file_system_image_path, file_system_save_dir);
    workbench::runWorkbench(file_system_image_path, file_system_save_dir);





    // todo: config files track everything I'm tempted to comment out
    // app::mainLoop(file_system_image_path, file_system_save_dir);

   


    


    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Main.cpp execution time: " << elapsed.count() << " s" << endl;






    return 0;
}


