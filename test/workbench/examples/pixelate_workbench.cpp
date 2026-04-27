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
        for (auto idx : r) { 
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


        logger.start("random");
        uint32_t seed = 93u;
        uint32_t random_int = random_gen::lcg(seed);
        cout << "random int: " << random_int << endl;
        int num_random_iterations = 10;
        cout << num_random_iterations << "more rands: ";
        for (int i = 0; i < num_random_iterations; i++){ 
            cout << random_gen::lcg(1<<i) << " ";
        }        
        cout << endl;

        cout << "random sequence: " << endl;
        vector<int> random_vec = math::sequence::randomSamples(min, max, num_idx, seed);
        for (auto n : random_vec) { 
            cout << n << " ";
        }
        cout << endl;

        logger.stop("random");





        logger.start("sequence params");
        variant_fn::SequenceCommon s;
        s.min = 10;
        s.max = 1000;
        s.num_elements = 10;
        s.ratio = 0.5;
        using st = variant_fn::SequenceMode;
        s.mode = st::uniform;
        vector<int> seq = variant_fn::sequenceFn(s);
        for (auto idx : seq) { cout << idx << " ";}
        cout << endl;
        logger.stop("sequence params");



        logger.start("run pixelate");

        // --- load image ---
        Image original_img = image::io::loadImageFileSystem(image_path);

        // -- load params --- 

        variant_fn::SequenceCommon seq_x;
        seq_x.mode = st::ratio;
        seq_x.min = 0;
        seq_x.max = original_img.getWidth();
        seq_x.num_elements = 20;
        seq_x.ratio = 0.5; // todo: default values for these
        
        variant_fn::SequenceCommon seq_y;
        seq_y.mode = st::ratio;
        seq_y.min = 0;
        seq_y.max = original_img.getHeight();
        seq_y.num_elements = 10;
        seq_y.ratio = 0.25;

        pixelate::Parameters params;
        params.seq_x_common = seq_x;
        params.seq_y_common = seq_y;
        pixelate::Pixelate my_pixelate(params);

        // --- run pipeline --- 

        pixelate::Cache cache;
        cache.original = original_img;

        my_pixelate.init(cache);
        my_pixelate.run(cache);

        logger.stop("run pixelate", cache.canvas);
        


    }
}