#include "pixelate_workbench.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"                  // todo: if we include io we also want image.hpp
#include "../../src/pipelines/pixelate/pixelate.hpp"
#include "../../src/data/shapes/shapes.hpp"
#include "../../src/functions/math/sequence.hpp"
#include "../../src/functions/math/constants.hpp"
#include "../../src/variants/math/sequence_variants.hpp"
#include "../../src/functions/random/random.hpp"
#include <vector>
#include <iostream>

using namespace image;
using namespace std;


// todo: all pipeline workbenches together in one file

namespace workbench { 
    void runPixelate(string image_path, Logger logger) { 

        cout << "hello from pixelate workbench" << endl;


        // common
        int min = 0;
        int max = 100000;
        

        logger.start("ratio");
        double ratio = math::constants::inv_phi;
        vector<int> r = math::sequence::ratioSamples(min, max, ratio);
        shapes::printVector<int>(r);
        cout << endl;
        logger.stop("ratio");


        logger.start("even");
        int num_idx = 12;
        vector<int> even = math::sequence::uniformSamplesBounds(min, max, num_idx); 
        shapes::printVector<int>(r);
        cout << endl;
        logger.stop("even");


       





        



        

        // --- load image ---
        Image original_img = image::io::loadImageFileSystem(image_path);

        // -- load params --- 

        using mode = variant_fn::SequenceMode;

        variant_fn::SequenceCommon seq_x;
        seq_x.mode = mode::ratio;
        seq_x.min = 0;
        seq_x.max = original_img.getWidth();
        seq_x.num_elements = 4;
        seq_x.ratio = 0.5; // todo: default values for these
        seq_x.seed = 300;
        
        variant_fn::SequenceCommon seq_y;
        seq_y.mode = mode::random;
        seq_y.min = 0;
        seq_y.max = original_img.getHeight();
        seq_y.num_elements = 5;
        seq_y.ratio = 0.25;
        seq_y.seed = 100;

        pixelate::Parameters params;
        params.seq_x_common = seq_x;
        params.seq_y_common = seq_y;

        // --- load cache ---

        pixelate::Cache cache;
        cache.original = original_img;
        

        // --- run pipeline --- 
        logger.start("run pixelate");
        pixelate::Pixelate my_pixelate(params);
        
        my_pixelate.init(cache);
        cout << "cache.ax: " << endl << cache.ax << endl;

        my_pixelate.run(cache);

        logger.stop("run pixelate", cache.canvas);

        // --- run multiple times ---
        
        for (int i = 2; i < 100; i += 2) { 
            std::string task_name = "run pixelate: " + std::to_string(i); // todo logger handles many tests with same name elegantly
            logger.start(task_name);

            params.seq_x_common.num_elements = i;
            params.seq_x_common.seed = 300 + 1000*i;

            params.seq_y_common.num_elements = i;
            params.seq_y_common.seed = 500 + 700*i;


            pixelate::Pixelate my_pixelate_scoped(params); // todo rule of 5 pipelines
            my_pixelate_scoped.init(cache);
            my_pixelate_scoped.run(cache);
            logger.stop(task_name, cache.canvas);

        }

        


    }
}