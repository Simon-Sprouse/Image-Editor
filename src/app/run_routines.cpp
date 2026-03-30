#include "run_routines.hpp"

#include "../routines/mosaic/mosaic.hpp"
#include "../routines/pop_art/pop_art.hpp"

#include <iostream>
#include <string>


using std::string, std::cout, std::endl;




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
        params.num_splits = 3;

        pop_art::PopArt my_pop_art(params);
        my_pop_art.loadExistingImage(image);
        my_pop_art.run();

        ImageResult output;
        output.label = "pop_art";
        output.image = my_pop_art.getCanvas();

        return output;

    }



}