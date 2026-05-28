#pragma once

#include "../logger.hpp"
#include "../../../src/data/image/color_map.hpp"
#include "../../../src/data/image/primitives.hpp"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace logger;

namespace workbench { 

    void colorMapUsage(string image_path, Logger logger);
    Image<RGB> makeTileCheckerNxN(vector<Image<RGB>> tiles, const int N);
    Image<RGB> makeTileNxN(vector<Image<RGB>> tiles, const int N);
    vector<Point> getTileCornersNxN(Size size, const int N);
    Image<RGB> makeColumnImg(Size size, const Color_Map& cmap);
    Image<RGB> makeRowImg(Size size, const Color_Map& cmap);
    Image<RGB> tileChecker4x4(const vector<Image<RGB>> img_vector);
    void copyRegion(const Image<RGB>& src_img, Image<RGB>& dst_img, Point tl=Point(0, 0));
}