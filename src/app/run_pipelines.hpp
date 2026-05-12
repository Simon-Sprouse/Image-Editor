#pragma once 

#include "app.hpp"
using namespace image;

namespace app {

    ImageResult runMosaic(const Image<RGBA>& image);
    ImageResult runPopArt(const Image<RGBA>& image);
    ImageResult runPopArtSlow(const Image<RGBA>& image);
    ImageResult runGrid(const Image<RGBA>& image);
    ImageResult runPixelate(const Image<RGBA>& image);

}