#include "run_pipelines.hpp"

#include "../pipelines/mosaic/mosaic.hpp"
#include "../pipelines/pop_art/pop_art.hpp"
#include "../pipelines/grid/grid.hpp"
#include "../pipelines/pixelate/pixelate.hpp"
#include "../data/shapes/shapes.hpp"
#include "../functions/math/sequence.hpp"
#include "../variants/math/sequence_variants.hpp"

#include <iostream>
#include <string>


using std::string, std::cout, std::endl;
using shapes::Rect;
using seq_common = variant_fn::SequenceCommon;
using seq_mode = variant_fn::SequenceMode;



namespace app { 


    /*
    ---------------
        Mosaic
    ---------------
    */

    ImageResult runMosaic(const Image& image) { 

        mosaic_gen::Parameters params;
        params.resize_factor = 0.5;
        params.blur_kernel_size = 3;
        params.blur_sigma = 1.4;
        params.canny_threshold_1 = 50;
        params.canny_threshold_2 = 100;
        params.max_segment_angle_rad = 100 * M_PI / 180.0; // TODO why is this in rad
        params.min_segment_length = 20;
        params.segment_angle_window = 10;
        params.tile_size = 10;
        params.number_of_rings = 3;
        params.initial_step = 1.5 * params.tile_size;
        params.step_size = 0.25 * params.tile_size;
        params.min_intersection_distance = 0.25 * params.tile_size;
        params.max_frontiers = 7;
        params.flood_fill_neighbor_points = 4;
        params.distance_from_center = 1.5 * params.tile_size;
        params.random_background_points = 50000;
        params.canny_resize_factor = 0.4;
        // params.tiles_per_frame = 20;
        // params.jitter_map.insert({4, 0});
        // params.jitter_map.insert({8, 1});
        // params.jitter_map.insert({12, 10});

        int squeeb = 42;
    

        mosaic_gen::Mosaic my_mosaic(params);
        my_mosaic.loadExistingImage(image);
        my_mosaic.runAll();

        ImageResult output;
        output.label = "mosaic";
        output.image = my_mosaic.getCanvas();

        return output;

    }



    /*
    ---------------
        Pop Art
    ---------------
    */

    ImageResult runPopArt(const Image& image) { 

        pop_art::Parameters params;
        params.num_splits = 4;

        pop_art::PopArt my_pop_art(params);
        my_pop_art.loadExistingImage(image);
        my_pop_art.run();

        ImageResult output;
        output.label = "pop_art";
        output.image = my_pop_art.getCanvas();

        return output;

    }

    ImageResult runPopArtSlow(const Image& image) { 

        pop_art::Parameters params;
        params.num_splits = 4;

        pop_art::PopArt my_pop_art(params);
        my_pop_art.loadExistingImage(image);
        my_pop_art.runSlow();

        ImageResult output;
        output.label = "pop_art";
        output.image = my_pop_art.getCanvas();

        return output;

    }

    ImageResult runGrid(const Image& image) { 

        seq_common seq_x;
        seq_x.mode = seq_mode::uniform;
        seq_x.min = 0;
        seq_x.max = image.getWidth();
        seq_x.ratio = 0.5;
        seq_x.num_elements = 10;

        seq_common seq_y;
        seq_y.mode = seq_mode::ratio;
        seq_y.min = 0;
        seq_y.max = image.getHeight();
        seq_y.ratio = 0.5;
        seq_y.num_elements = 40;

        grid::Parameters p;
        p.seq_x_common = seq_x;
        p.seq_y_common = seq_y;
        p.thickness = 3;

        grid::Cache cache;
        cache.original = image.clone();

        grid::Grid my_grid(p);
        my_grid.init(cache);
        my_grid.run(cache);


        ImageResult output;
        output.label = "grid";
        output.image = cache.canvas;

        return output;

    }


    ImageResult runPixelate(const Image& image) { 

        seq_common seq_x;
        seq_x.mode = seq_mode::uniform;
        seq_x.min = 0;
        seq_x.max = image.getWidth();
        seq_x.ratio = 0.5;
        seq_x.num_elements = 40;

        seq_common seq_y;
        seq_y.mode = seq_mode::ratio;
        seq_y.min = 0;
        seq_y.max = image.getHeight();
        seq_y.ratio = 0.5;
        seq_y.num_elements = 20;

        pixelate::Parameters p;
        p.seq_x_common = seq_x;
        p.seq_y_common = seq_y;

        pixelate::Cache cache;
        cache.original = image.clone();

        pixelate::Pixelate my_pixelate(p);
        my_pixelate.init(cache);
        my_pixelate.run(cache);


        ImageResult output;
        output.label = "pixelate";
        output.image = cache.canvas;

        return output;
    }



}