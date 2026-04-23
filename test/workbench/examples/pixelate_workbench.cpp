#include "pixelate_workbench.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"                  // todo: if we include io we also want image.hpp
#include "../../src/routines/pixelate/pixelate.hpp"
#include "../../src/data/shapes/shapes.hpp"
#include <vector>
#include <iostream>

using namespace image;
using namespace std;

namespace workbench { 
    void runPixelate(string image_path, Logger logger) { 

        cout << "hello from pixelate workbench" << endl;


        logger.start("init");

        
        vector<Rect> rectangles;
        pixelate::Parameters params;
        params.rectangles = rectangles;
        pixelate::Pixelate my_pixelate(params);

        Image original = image::io::loadImageFileSystem(image_path);
        my_pixelate.init(original);

        my_pixelate.run();
        logger.stop("init", my_pixelate.getCanvas());



    }
}