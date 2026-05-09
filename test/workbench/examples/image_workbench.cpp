#include "image_workbench.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include <iostream>

using namespace logger;
using namespace image;
using namespace std;

namespace workbench { 
    void runImage(string image_path, Logger logger) { 

        

        logger.start("image load");
        Image original = io::loadImageFileSystem(image_path);
        

        logger.stop("image load");


        logger.start("image read");

        int sum_r = 0;
        for (auto px : original) { 
            sum_r += px.r;
        }
        cout << "sum r: " << sum_r << endl;

        logger.stop("image read");



        logger.start("image fill");
        original.fill(Color(255, 255, 255));
        logger.stop("image fill");





    }
}