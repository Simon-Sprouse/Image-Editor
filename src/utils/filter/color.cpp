#include "color.hpp"



#include <vector>

using image::Image, image::Size, image::Color, image::Point;

namespace filter::color { 



    // todo maybe extend this function to take a vector (although this implies copy in caller syntax)
    // todo maybe perform sampling of grid pixels not whole image
    Color avgColor(const Image& image, const Point& tl_corner, int dx, int dy) { 

        // todo structured bindings to extract r, g, b, a from color? 
        // todo get iterator to work with const image and const point
        
        // int total_r = 0;
        // int total_g = 0;
        // int total_b = 0;

        // int width = image.getWidth();

        // int pointer = image.getLinearIndex(tl_corner);
        // Color color; 
        // for (int y = 0; y < dy; y++) { 
        //     for (int x = 0; x < dx; x++) { 
        //         color = image.at(pointer + x); // todo structured bindings? 
        //         total_r += color.r;
        //         total_g += color.g;
        //         total_b += color.b;
        //     }
        //     pointer += width;
        // }

        // int num_pixels = dx * dy;
        // return Color(total_r / num_pixels, total_g / num_pixels, total_b / num_pixels);



        int total_r = 0;
        int total_g = 0;
        int total_b = 0;

        for (auto row : image.regionRows(tl_corner, dx, dy)) { 
            for (auto c : row) { 
                total_r += c.r;
                total_g += c.g;
                total_b += c.b;
            }
        }
        int num_pixels = dx * dy;
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