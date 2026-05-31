#include "tile_test.hpp"
#include "../../../src/functions/graphics/tile.hpp"
#include "../../../src/data/image/color_map.hpp"

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
            int num_colors = 11;
            // todo bug seg fault when trying to use the COSMOS map itself
            Color_Map cmap = Color_Map(image::VIRIDIS_STOPS, 1000);
            

            int canvas_size = 1000;
            vector<int> num_tiles = {1, 2, 3, 4, 5, 10, 50, 100, 1000};

            for (int N : num_tiles) { 
                string test_name = "tile_image " + to_string(N) + "x" + to_string(N);
                logger.start(test_name);

                // Compute images for each tile type, pre-arragement
                vector<Image<RGB>> tiles_vector;
                for (int i = 0; i < num_colors; i++) { 
                    Size tile_size = Size(canvas_size / N);
                    cout << "color: " << cmap.frac(i, num_colors).to<RGB>() << endl;
                    tiles_vector.emplace_back(Image<RGB>(tile_size, cmap.frac(i, num_colors).to<RGB>()));
                }

                // Arrange tile images in tile pattern
                Image<RGB> tile_image = draw::tile::makeTileNxN(tiles_vector, N);


                logger.stop(test_name, tile_image);
            }   

        }



        // TEST NxN Checker tiling pattern
        {}








    }

}
