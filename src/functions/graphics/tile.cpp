#include "tile.hpp"

#include "../math/sequence.hpp"

#include <iostream>

using namespace image;
using namespace std;

namespace draw::tile { 


    void tileTest() { 
        cout << "hello from tile test" << endl;
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


    Image<RGB> makeTileNxN(vector<Image<RGB>> tiles, const int N) { 
        // todo input validation
        // todo maybe fill could be used better here? 
        Size tile_size = tiles.at(0).size();
        Size canvas_size = tile_size * N; // fine because NxN implies square tiles
        Image<RGB> canvas = Image<RGB>(canvas_size); 
        
        vector<Point> points = getTileCornersNxN(canvas_size, N); // tl corners
        int tile_idx = 0; // to rotate through tiles
        int num_unique_tiles = tiles.size();
        for (const Point& pt : points) { 

            // TODO move this to img.copyRegion(Rect R, const Image& src);
            copyRegion(tiles.at(tile_idx), canvas, pt);
            tile_idx++;
            tile_idx %= num_unique_tiles;
        }
        return canvas;
    }

    vector<Point> getTileCornersNxN(Size size, const int N) { 
        // todo input validation
        vector<Point> output;
        output.reserve(N*N);
        vector<int> intervals = math::sequence::uniformIntervals(0, size.width, N+1);
        intervals.pop_back(); // last point is at far right / bottom border
        for (int y : intervals) { 
            for (int x : intervals) { 
                output.push_back(Point(x, y));
            }
        }
        return output;
    }


    Image<RGB> makeTileCheckerNxN(vector<Image<RGB>> tiles, const int N) { 
        // todo input validation
        Size tile_size = tiles.at(0).size();
        Size canvas_size = tile_size * N; // fine because NxN implies square tiles
        Image<RGB> canvas = Image<RGB>(canvas_size); 
        
        vector<Point> points = getTileCornersNxN(canvas_size, N); // tl corners
        int num_unique_tiles = tiles.size();

        int start_offset = 0;
        for (int y = 0; y < N; y++) { 
            int tile_index = start_offset;
            for (int x = 0; x < N; x++) { 

                Point pt = points.at(y*N + x);
                copyRegion(tiles.at(tile_index), canvas, pt);

                tile_index++;
                tile_index %= num_unique_tiles;
            }
            start_offset++;
            start_offset %= num_unique_tiles;
        }

        return canvas;
    }

}