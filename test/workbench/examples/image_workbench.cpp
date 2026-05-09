#include "image_workbench.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include <iostream>

using namespace logger;
using namespace image;

using namespace std;

#include <opencv2/opencv.hpp>


namespace workbench { 
    void runImage(string image_path, Logger logger) { 

        

        logger.start("image load");
        Image<RGBA> original = io::loadImageFileSystem(image_path);
        

        logger.stop("image load");


        logger.start("image read");

        int sum_r = 0;
        for (auto px : original) { 
            sum_r += px.r;
        }
        cout << "sum r: " << sum_r << endl;

        logger.stop("image read");







        image::RGBA rgba(0);

        image::HSV a(0);
        cout << a << endl;

        image::HSV b(1000, 20, 20);
        cout << b << endl;

        image::GRAY c(240);
        cout << c << endl;












    }
}