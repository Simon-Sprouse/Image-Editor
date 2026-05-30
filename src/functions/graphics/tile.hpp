#pragma once 

#include "../../data/image/image.hpp"

#include <vector>

using namespace image;
using namespace std;


namespace draw::tile {

    void tileTest();

    void copyRegion(const Image<RGB>& src_img, Image<RGB>& dst_img, Point tl);

    Image<RGB> makeTileNxN(vector<Image<RGB>> tiles, const int N);
    vector<Point> getTileCornersNxN(Size size, const int N);
    Image<RGB> makeTileCheckerNxN(vector<Image<RGB>> tiles, const int N);
}