#pragma once 

#include "app.hpp"
using namespace image;

namespace app {

    ImageResult runMosaic(const Image<RGB>& image);
    ImageResult runPopArt(const Image<RGB>& image);
    ImageResult runPopArtSlow(const Image<RGB>& image);
    ImageResult runGrid(const Image<RGB>& image);
    ImageResult runPixelate(const Image<RGB>& image);

}