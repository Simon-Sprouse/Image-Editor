#include "tile_test.hpp"
#include "../../../src/functions/graphics/tile.hpp"

#include <iostream>

namespace workbench { 

    void tileUsage(string image_path, Logger logger) { 


        // TEST helper files live in tile.hpp / tile.cpp
        {
            cout << "Hello from tile usage test " << endl;
            draw::tile::tileTest();
        }




        // TEST NxN Row Major iteration tiling pattern 
        {

            // define gradient for tiles (todo using cmap)
            RGB color_0 = RGB(255, 0, 0);
            RGB color_1 = RGB(0, 255, 0);
            RGB color_2 = RGB(0, 0, 255);

            

            int canvas_size = 1000;
            vector<int> num_tiles = {1, 2, 3, 4, 5, 10, 1000};

            for (int N : num_tiles) { 
                string test_name = "tile_image " + to_string(N) + "x" + to_string(N);
                logger.start(test_name);

                // Compute images for each tile type, pre-arragement
                Size tile_size = Size(canvas_size / N);
                Image<RGB> tile_0 = Image<RGB>(tile_size, color_0);
                Image<RGB> tile_1 = Image<RGB>(tile_size, color_1);
                Image<RGB> tile_2 = Image<RGB>(tile_size, color_2);

                vector<Image<RGB>> tiles_vector = {tile_0, tile_1, tile_2};

                // Arrange tile images in tile pattern
                Image<RGB> tile_image = draw::tile::makeTileNxN(tiles_vector, N);


                logger.stop(test_name, tile_image);
            }   

        }



        // TEST NxN Checker tiling pattern
        {}








    }

}
