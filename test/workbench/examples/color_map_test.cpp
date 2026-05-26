#include "color_map_test.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/functions/graphics/line.hpp"
#include "../../../src/functions/graphics/polygon.hpp"
#include "../../../src/data/shapes/shapes.hpp"

#include "../logger.hpp"

#include <iostream>
#include <array>
#include <cstring>

using namespace std;
using namespace logger;
using namespace image;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger) {

        cout << "hello from color map usage" << endl;

        
        // todo test lerp independently


        // 1
        {
            HSV c_0 = HSV(600, 100, 100);
            HSV c_1 = HSV(900);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 1: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 2
        {
            HSV c_0 = HSV(900);
            HSV c_1 = HSV(600, 100, 100);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 2: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 3
        {
            HSV c_0 = HSV(1400);
            HSV c_1 = HSV(100);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 3: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }
        // 4
        {
            HSV c_0 = HSV(100);
            HSV c_1 = HSV(1400);
            vector<HSV> lerp_results = lerpMulti(c_0, c_1, 4);
            cout << "scenario 4: " << endl;
            for (auto color : lerp_results) { 
                cout << color << endl;
            }
            cout << endl;
        }




        cout << endl; 





        {
            HSV color_0(1200, 255, 50);
            HSV color_1(150, 150, 255);


            Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
            Color_Stop stop_1 = Color_Stop(color_1, 1.0f);

            vector<Color_Stop> stops = {stop_0, stop_1};

            int side = 1000;
            Image<RGB> img(Size(side, side));


            string cmap_base_name = "Create Color Map - LUT Size: ";
            string draw_base_name = "Draw Color Map - LUT Size: ";
            int num_iterations = 3;
            int step = 3;
            int start = 2;
            for (int i = start; i < num_iterations*step; i += step) { 

                Color_Map cmap = Color_Map(stops, i);

                logger.start(draw_base_name + to_string(i));
                for (int x = 0; x < img.getWidth(); x++) { 
                    draw::line::drawCol(img, x, cmap.frac(x, side).to<RGB>());
                }
                logger.stop(draw_base_name + to_string(i), img);
                cout << endl;
            }
        }
        


















        // art piece


        {
            
            // define gradient
            int base = 1150;
            int step = 150;
            HSV color_0(base, 210, 30);   // Deep burnt orange
            HSV color_1(base + step*1, 240, 60);   // Vivid orange
            HSV color_2(base + step*2, 210, 180);   // Golden yellow
            HSV color_3(base + step*4, 100, 240);   // Pink-magenta
            Color_Stop stop_0 = Color_Stop(color_0, 0.0f);
            Color_Stop stop_1 = Color_Stop(color_1, 0.3f);
            Color_Stop stop_2 = Color_Stop(color_2, 0.7f);
            Color_Stop stop_3 = Color_Stop(color_3, 1.0f);
            vector<Color_Stop> stops = {stop_0, stop_1, stop_2, stop_3};
            int num_columns = 9;
            Color_Map cmap = Color_Map(stops, num_columns);

            

            // test column image
            {
                logger.start("column image test");
                Image<RGB> column_img = makeColumnImg(Size(1000, 1000), cmap);
                logger.stop("column image test", column_img); // todo badly need separate imshow
            }

            // test copy 
            {
                logger.start("image copy test");
                Size size_0 = Size(3200, 3200);
                Image<RGB> canvas = Image<RGB>(size_0, RGB(0));
                

                Size size_1 = size_0 * 0.5f;
                Image<RGB> row_img = makeRowImg(size_1, cmap);
                copyRegion(row_img, canvas, Point(0, 0));

                Size size_2 = size_1 * 0.5f;
                Image<RGB> row_img_1 = makeRowImg(size_2, cmap);
                Image<RGB> col_img_1 = makeColumnImg(size_2, cmap);
                vector<Image<RGB>> tile_vector = {row_img_1, col_img_1};
                Image<RGB> tile_4x4 = tileChecker4x4(tile_vector);
                copyRegion(tile_4x4, canvas, Point(1600, 0));

                Size size_3 = size_2 * 0.5f;
                Image<RGB> row_img_2 = makeRowImg(size_3, cmap);
                Image<RGB> col_img_2 = makeColumnImg(size_3, cmap);
                vector<Image<RGB>> tile_vector_1 = {row_img_2, col_img_2};
                Image<RGB> tile_4x4_1 = tileChecker4x4(tile_vector_1);
                vector<Image<RGB>> vector_of_tiles = {tile_4x4_1, tile_4x4_1, tile_4x4_1, tile_4x4_1};
                Image<RGB> tile_tile = tileChecker4x4(vector_of_tiles);
                copyRegion(tile_tile, canvas, Point(0, 1600));

                Size size_4 = size_3 * 0.5f;
                Image<RGB> row_img_3 = makeRowImg(size_4, cmap);
                Image<RGB> col_img_3 = makeColumnImg(size_4, cmap);
                vector<Image<RGB>> tile_vector_2 = {row_img_3, col_img_3};
                Image<RGB> tile_4x4_2 = tileChecker4x4(tile_vector_2);
                vector<Image<RGB>> vector_of_tiles_1 = {tile_4x4_2, tile_4x4_2, tile_4x4_2, tile_4x4_2};
                Image<RGB> tile_tile_1 = tileChecker4x4(vector_of_tiles_1);
                vector<Image<RGB>> vector_tile_tiles = {tile_tile_1, tile_tile_1, tile_tile_1, tile_tile_1};
                Image<RGB> tile_tile_tile = tileChecker4x4(vector_tile_tiles);
                copyRegion(tile_tile_tile, canvas, Point(1600, 1600));



                // copyRegion(column_img, canvas, Point(0, 1000));
                // copyRegion(column_img, canvas, Point(1000, 1000));
                logger.stop("image copy test", canvas);
            }



                

 







        }







    }


    // create column image
    Image<RGB> makeColumnImg(Size size, const Color_Map& cmap) { 
        Image<RGB> img(size);
        for (int x = 0; x < size.width; x++) { 
            draw::line::drawCol(img, x, cmap.frac(x, size.width).to<RGB>());
        }
        return img;
    }

    // todo these could be way more efficient
    Image<RGB> makeRowImg(Size size, const Color_Map& cmap) { 
        Image<RGB> img(size);
        for (int y = 0; y < size.height; y++) { 
            draw::line::drawRow(img, y, cmap.frac(y, size.height).to<RGB>());
        }
        return img;
    }
    
    // todo: tiling is a meta routine
    Image<RGB> tileChecker4x4(const vector<Image<RGB>> img_vector) { 
        // todo input validation all images the same size, and all square
        int side = img_vector[0].getWidth();
        Image<RGB> canvas = Image<RGB>(Size(side * 2, side*2)); // 4x4 canvas
        // todo getPoints();
        copyRegion(img_vector[0], canvas, Point(0, 0));
        copyRegion(img_vector[1], canvas, Point(side, 0));
        copyRegion(img_vector[1], canvas, Point(0, side));
        copyRegion(img_vector[0], canvas, Point(side, side));
        return canvas;
    }

    // copy region todo: should live in image ecosystem
    void copyRegion(const Image<RGB>& src_img, Image<RGB>& dst_img, Point tl) { 
        // todo input validation
        int row_size = src_img.getWidth();
        for (int y = 0; y < src_img.getHeight(); y++) { 
            const RGB* src_ptr = src_img.rowPtr(y);
            RGB* dst_ptr = dst_img.rowPtr(y + tl.y) + tl.x;
            std::memcpy(dst_ptr, src_ptr, sizeof(RGB)*row_size);
        }
    }







}