#include "image_workbench.hpp"
#include "../../../src/data/image/image.hpp"
#include "../../../src/data/image/io.hpp"
#include <iostream>

using namespace logger;
using namespace image;

using namespace std;

#include <opencv2/opencv.hpp>


namespace workbench { 

    void runPrimitives(string image_path, Logger logger) { 


        logger.start("constructors");
        {
            image::RGBA rgba(0);

            image::HSV a(0);
            cout << a << endl;

            image::HSV b(1000, 20, 20);
            cout << b << endl;

            image::GRAY c(240);
            cout << c << endl;
        
        }
        logger.stop("constructors"); // todo make these legit



        logger.start("conversions");
        {

            RGBA rgba(210, 42, 69);
            HSV hsv(1234, 73, 21);
            GRAY gray(93);

            cout << "RGBA: " << rgba << endl;
            cout << "RGBA.toGRAY(): " << rgba.toGray() << endl;
            // cout << "RGBA.toHSV(): " << rgba.toHSV() << endl;



            HSV test = RGBA2HSV(rgba);
            cout << "HSV: " << test << endl;


        }
        logger.stop("conversions");





    }













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







       










    }
}