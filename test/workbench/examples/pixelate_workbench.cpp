#include "pixelate_workbench.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"                  // todo: if we include io we also want image.hpp
#include "../../src/routines/pixelate/pixelate.hpp"
#include "../../src/data/shapes/shapes.hpp"
#include "../../utils/math/sequence.hpp"
#include <vector>
#include <iostream>

using namespace image;
using namespace std;

// todo: all routine workbenches together in one file

namespace workbench { 
    void runPixelate(string image_path, Logger logger) { 

        cout << "hello from pixelate workbench" << endl;


        logger.start("init");

        Image original = image::io::loadImageFileSystem(image_path);

        
        // todo rethink parameters
        int num_cols = 40; // todo these actually are named off by one bc they are indexes
        int num_rows = 12;
        vector<int> cols = math::sequence::uniformSamplesBounds(0, original.getWidth(), num_cols); 
        vector<int> rows = math::sequence::uniformSamplesBounds(0, original.getHeight(), num_rows);
        Axis_Table ax{cols, rows};

        pixelate::Parameters params;
        params.ax = ax;

        pixelate::Pixelate my_pixelate(params);
        my_pixelate.init(original);
        my_pixelate.run();

        logger.stop("init", my_pixelate.getCanvas());



    }
}