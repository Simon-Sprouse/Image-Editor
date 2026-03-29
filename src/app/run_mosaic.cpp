#include <iostream>

#include "run_mosaic.hpp"
#include "../routines/mosaic/mosaic.hpp"
#include "../data/image/io.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


using std::cout, std::string, std::endl;
using mosaic_gen::Mosaic, mosaic_gen::Parameters;

namespace app {
    void runMosaic(string image_path, string save_dir) { 

            Parameters params;
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


            Image img = image::io::loadImageFileSystem(image_path);
            cout << "Loaded image from: " << image_path << endl;
            cout << "Original Dimensions: " << img.size() << endl;

            Mosaic my_mosaic(params);
            my_mosaic.loadExistingImage(img);
            my_mosaic.runAll();

            cout << "Results Dimensions: " << my_mosaic.getCanvas().size() << endl;
            string save_path = save_dir + "result.jpg";
            image::io::saveImageFileSystem(my_mosaic.getCanvas(), save_path);





            cv::Mat image_mat = image::io::imageToCvMat(img);
            cout << "image_mat.size()" << image_mat.size() << endl;



            cv::namedWindow("test_window", cv::WINDOW_AUTOSIZE);
            cv::imshow("test_window", image_mat);
            cv::waitKey(0);
            cv::destroyAllWindows();



    }
}