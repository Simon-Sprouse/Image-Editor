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


       

        // common
        int min = 0;
        int max = 100000;

        logger.start("fib");
        vector<int> fib = math::sequence::goldenRatioSamples(min, max);
        for (auto idx : fib) { 
            cout << idx << " ";
        }
        cout << endl;
        logger.stop("fib");


        logger.start("even");
        int num_idx = 12;
        vector<int> even = math::sequence::uniformSamplesBounds(min, max, num_idx); 
        for (auto idx : even) { cout << idx << " ";}
        cout << endl;
        logger.stop("even");



        logger.start("sequence params");
        math::sequence::SequenceParams s;
        s.min = 10;
        s.max = 1000;
        s.num_elements = 10;
        using st = math::sequence::SequenceType;
        st type = st::uniform;
        vector<int> seq = math::sequence::sequenceSelector(s, type);
        for (auto idx : seq) { cout << idx << " ";}
        cout << endl;
        logger.stop("sequence params");



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