#include "grid_workbench.hpp"

#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"
using namespace image;

#include "../../src/routines/grid/grid.hpp"

#include <opencv2/opencv.hpp>

#include <string>
using namespace std;

#include <iostream>


namespace workbench { 

    void runGrid(Image image, string save_dir, string window_name) { 

        grid::Parameters params;
        params.rows = 30;
        params.cols = 40;
        params.thickness = 5;



        grid::Grid my_grid(params);
        my_grid.loadExistingImage(image);
        my_grid.computeRectCoords();

        
        cv::setWindowTitle(window_name, "original image");
        cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        cv::waitKey(0);

        my_grid.drawRectAreas();
        cv::setWindowTitle(window_name, "grid with rect areas");
        cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        cv::waitKey(0);

        my_grid.drawGridLines();
        cv::setWindowTitle(window_name, "grid with lines");
        cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
        cv::waitKey(0);






        for (int i = 1; i < 40; i++) { 

            my_grid.clearData();

            params.rows = 2 * i;
            params.cols = 3 * i;

            my_grid.setParameters(params);

            my_grid.computeRectCoords();
            my_grid.drawRectAreas();
            cv::setWindowTitle(window_name, "rect area: " + to_string(i));
            cv::imshow(window_name, io::imageToCvMat(my_grid.getCanvas()));
            cv::waitKey(0);

        }

    }
}
