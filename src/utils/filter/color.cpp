#include "color.hpp"

using image::Image, image::Size, image::Color;

namespace filter::color { 
    void toGrayscale(const Image& src, Image& dest) { 
        Size size = src.size();
        dest = Image(size);  // reallocate dest image with same size

        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x) {
                const Color& pixel = src.at(x, y);

                // Compute luminance (grayscale intensity)
                uint8_t gray = static_cast<uint8_t>(
                    0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b
                );
                Color new_pixel(gray, gray, gray);
                dest.setPixel(x, y, new_pixel);
            }
        }
    }
}