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
        const double inv_phi = 0.6180339887498948; // todo: better way to do this


        logger.start("ratio");
        vector<int> ratio = math::sequence::ratioSamples(min, max, inv_phi);
        for (auto idx : ratio) { 
            cout << idx << " ";
        }
        cout << endl;
        logger.stop("ratio");


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
        s.ratio = 0.5;
        using st = math::sequence::SequenceType;
        s.type = st::uniform;
        vector<int> seq = math::sequence::sequenceSelector(s);
        for (auto idx : seq) { cout << idx << " ";}
        cout << endl;
        logger.stop("sequence params");



        logger.start("run pixelate");

        Image original = image::io::loadImageFileSystem(image_path);

        // create sequence params
        using st = math::sequence::SequenceType;

        math::sequence::SequenceParams seq_x;
        seq_x.type = st::ratio;
        seq_x.min = 0;
        seq_x.max = original.getWidth();
        seq_x.num_elements = 20;
        seq_x.ratio = 0.5; // todo: default values for these
        
        math::sequence::SequenceParams seq_y;
        seq_y.type = st::ratio;
        seq_y.min = 0;
        seq_y.max = original.getHeight();
        seq_y.num_elements = 10;
        seq_y.ratio = 0.25;

        pixelate::Parameters params;
        params.seq_x = seq_x;
        params.seq_y = seq_y;

        pixelate::Pixelate my_pixelate(params);
        my_pixelate.init(original);
        my_pixelate.run();

        logger.stop("run pixelate", my_pixelate.getCanvas());
        


    }
}