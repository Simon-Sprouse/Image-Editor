#include "grid_workbench.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"
#include "../../src/routines/grid/grid.hpp"
#include "../../src/utils/math/sequence.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace image;
using grid::Grid, grid::Parameters, grid::Cache;
using seq = math::sequence::SequenceParams;
using seq_t = math::sequence::SequenceType;


namespace workbench { 

    void runGrid(string image_path, Logger logger) { 



        logger.start("run");
        Image original_img = io::loadImageFileSystem(image_path);

        // todo - input validation / default values
        // note - this block is the biggest downside of our pattern
        seq seq_x;
        seq_x.type = seq_t::uniform;
        seq_x.min = 0;
        seq_x.max = original_img.getWidth();
        seq_x.num_elements = 10;
        seq_x.ratio = 0.5;

        seq seq_y;
        seq_y.type = seq_t::ratio;
        seq_y.min = 0;
        seq_y.max = original_img.getHeight();
        seq_y.num_elements = 30;
        seq_y.ratio = 0.5;

        Parameters p;
        p.seq_x = seq_x;
        p.seq_y = seq_y;
        p.thickness = 3;

        Cache cache;
        cache.original = original_img;

        Grid my_grid(p);
        my_grid.init(cache);
        my_grid.run(cache);


        logger.stop("run", cache.canvas);












        // OLD PATTERN vv

        // Image image = image::io::loadImageFileSystem(image_path);

        // grid::Parameters params;
        // params.rows = 30;
        // params.cols = 40;
        // params.thickness = 5;
        // grid::Grid my_grid(params);


        // logger.start("original_image");
        // my_grid.loadExistingImage(image);
        // logger.stop("original_image", my_grid.getCanvas());


        // logger.start("draw areas");
        // my_grid.computeRectCoords();
        // my_grid.drawRectAreas();
        // logger.stop("draw areas", my_grid.getCanvas());

        // logger.start("draw grid lines");
        // my_grid.drawGridLines();
        // logger.stop("draw grid lines", my_grid.getCanvas());


        // // huge example for why function pointers are probably bad. 
        // for (int i = 1; i < 100; i++) { 

        //     my_grid.clearData();

        //     params.rows = 2 * i;
        //     params.cols = 3 * i;

        //     my_grid.setParameters(params);

        //     string task_name = "draw areas iter: " + to_string(i);
        //     logger.start(task_name);
        //     my_grid.computeRectCoords();
        //     my_grid.drawRectAreas();
        //     logger.stop(task_name, my_grid.getCanvas());

        // }


        // VERY OLD PATTERN vvv

        // cv::setWindowTitle(window_name, "original image");
        // cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        // cv::waitKey(0);

        // my_grid.drawRectAreas();
        // cv::setWindowTitle(window_name, "grid with rect areas");
        // cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        // cv::waitKey(0);

        // my_grid.drawGridLines();
        // cv::setWindowTitle(window_name, "grid with lines");
        // cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        // cv::waitKey(0);






        

    }
}
