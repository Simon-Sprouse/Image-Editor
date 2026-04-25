#include "color.hpp"



#include <vector>

using image::Image, image::Size, image::Color, image::Point;

namespace filter::color { 



    // todo maybe extend this function to take a vector (although this implies copy in caller syntax)
    // todo maybe perform sampling of grid pixels not whole image
    Color avgColor(const Image& image, const Rect& rect) { 

        
        // todo get iterator to work with const image and const point


        // todo structured bindings to extract r, g, b, a from color? 
        int total_r = 0;
        int total_g = 0;
        int total_b = 0;

        // todo overload iterator
        for (auto row : image.regionRows(rect)) { 
            for (auto c : row) { 
                total_r += c.r;
                total_g += c.g;
                total_b += c.b;
            }
        }
        int num_pixels = rect.dx * rect.dy;
        return Color(total_r / num_pixels, total_g / num_pixels, total_b / num_pixels);

    }




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