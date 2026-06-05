#include "tile_test.hpp"
#include "../../../src/functions/graphics/tile.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/functions/math/sequence.hpp"

#include <iostream>

namespace workbench { 

    void tileUsage(string image_path, Logger logger) { 


        // TEST helper files live in tile.hpp / tile.cpp
        {
            cout << "Hello from tile usage test " << endl;
            draw::tile::tileTest();
        }




        // // TEST NxN Row Major iteration tiling pattern 
        // {

        //     // define gradient for tiles (todo using cmap)
        //     Color_Map cmap = VIRIDIS;
            
        //     int canvas_size = 1000;
        //     vector<int> N_values = {1, 2, 4, 5, 10, 50, 100, 1000};

        //     for (int N : N_values) { 
        //         string test_name = "tile_image " + to_string(N) + "x" + to_string(N);
        //         logger.start(test_name);

        //         // Compute images for each tile type, pre-arragement
        //         vector<Image<RGB>> image_cache;
        //         int num_tiles = N*N;
        //         for (int i = 0; i < num_tiles; i++) { 
                    
        //             Size size = Size(canvas_size / N);
        //             RGB fill_color = cmap.step(i, num_tiles);

        //             image_cache.emplace_back(Image<RGB>(size, fill_color));
        //         }

        //         // Arrange tile images in tile pattern
        //         Image<RGB> tile_image = draw::tile::makeTileNxN(image_cache, N);


        //         logger.stop(test_name, tile_image);
        //     }   

        // }




        // TEST vector lerp - todo this should also live in color_map_test.cpp
        {
            // define gradient for tiles (todo using cmap)
            Color_Map cmap_1 = Color_Map(HSV(1200, 0, 0), HSV(150, 0, 0));
            Color_Map cmap_2 = Color_Map(HSV(1200, 255, 50), HSV(150, 150, 255));

            int canvas_size = 1000;
            int N = 5;
            int num_tiles = N * N;
            vector<float> pos_vector = math::sequence::uniformIntervalsUnit(100); // arbitrary 

            for (float pos : pos_vector) { 

                string test_name = "cmap level lerp (" + to_string(pos) + "%)";
                logger.start(test_name);

                // get new cmap for this pos (between the two cmaps)
                Color_Map new_cmap = Color_Map(cmap_1, cmap_2, pos);

                // Compute images for each tile type, pre-arragement
                vector<Image<RGB>> image_cache;
                for (int i = 0; i < num_tiles; i++) { 
                    
                    Size size = Size(canvas_size / N);
                    RGB fill_color = new_cmap.step(i, num_tiles);

                    image_cache.emplace_back(Image<RGB>(size, fill_color));
                }

                // Arrange tile images in tile pattern
                Image<RGB> tile_image = draw::tile::makeTileNxN(image_cache, N);


                logger.stop(test_name, tile_image);
            }   

        }








    }

}
