#pragma once 

#include "app.hpp"

namespace app {

    ImageResult runMosaic(const Image& image);
    ImageResult runPopArt(const Image& image);
    ImageResult runPopArtSlow(const Image& image);
    ImageResult runGrid(const Image& image);
    ImageResult runPixelate(const Image& image);

}