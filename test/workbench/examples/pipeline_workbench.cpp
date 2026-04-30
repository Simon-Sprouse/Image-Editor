#include "pipeline_workbench.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"                  // todo: if we include io we also want image.hpp
#include "../../src/pipelines/pixelate/pixelate.hpp"
#include "../../src/pipelines/grid/grid.hpp"
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

        // --- load image ---
        Image original_img = image::io::loadImageFileSystem(image_path);

        // -- load params --- 

        using mode = variant_fn::SequenceMode;

        variant_fn::SequenceCommon seq_x;
        seq_x.mode = mode::random;
        seq_x.min = 0;
        seq_x.max = original_img.getWidth();
        seq_x.num_elements = 4;
        seq_x.ratio = 0.5; // todo: default values for these
        // seed given by default which is clock
        
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
        
        for (int i = 2; i < 20; i += 2) { 
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




    void runGrid(string image_path, Logger logger) {

        using namespace grid;

        
        Image original_img = io::loadImageFileSystem(image_path);
        original_img.fill(Color(255, 240, 220)); // todo improve fill method

        // todo - input validation / default values
        // note - this block is the biggest downside of our pattern
        variant_fn::SequenceCommon seq_x;
        seq_x.mode = variant_fn::SequenceMode::random;
        seq_x.min = 0;
        seq_x.max = original_img.getWidth();
        seq_x.num_elements = 10;
        seq_x.ratio = 0.5;

        variant_fn::SequenceCommon seq_y;
        seq_y.mode = variant_fn::SequenceMode::random;
        seq_y.min = 0;
        seq_y.max = original_img.getHeight();
        seq_y.num_elements = 30;
        seq_y.ratio = 0.5;

        Parameters p;
        p.seq_x_common = seq_x;
        p.seq_y_common = seq_y;
        p.thickness = 3;

        Cache cache;
        cache.original = original_img;

        // --- Run Once --- 
        logger.start("run");
        {
            Grid my_grid(p);
            my_grid.init(cache);
            my_grid.run(cache);

            logger.stop("run", cache.canvas);
        }
        
        // --- Run Multiple Num_Elements ---
        {
            for (int i = 2; i < 40; i += 2) { 
                std::string task_name = "run grid multiple: " + std::to_string(i); // todo logger handles many tests with same name elegantly
                logger.start(task_name);

                p.seq_x_common.num_elements = i;
                p.seq_x_common.seed = 300 + 1000*i;

                p.seq_y_common.num_elements = i;
                p.seq_y_common.seed = 500 + 700*i;


                Grid my_grid(p); // todo rule of 5 pipelines
                my_grid.init(cache);
                my_grid.run(cache);
                logger.stop(task_name, cache.canvas);

            } 
        }


        // --- Run Multiple Seeds  ---
        {
            p.seq_x_common.num_elements = 10;
            p.seq_y_common.num_elements = 10;

            for (int i = 0; i < 10; i++) { 
                std::string task_name = "run grid multiple seeds: " + std::to_string(i); // todo logger handles many tests with same name elegantly
                logger.start(task_name);

                p.seq_x_common.seed = 300 + 1000*i;
                p.seq_y_common.seed = 500 + 700*i;

                Grid my_grid(p); // todo rule of 5 pipelines
                my_grid.init(cache);
                my_grid.run(cache);
                logger.stop(task_name, cache.canvas);

            } 
        }


        

    }









}