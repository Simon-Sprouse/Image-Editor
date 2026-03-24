#pragma once

#include "../../data/image/image.hpp"

using image::Image;

namespace filter::color { 
    void toGrayscale(const Image& src, Image& dest);
}