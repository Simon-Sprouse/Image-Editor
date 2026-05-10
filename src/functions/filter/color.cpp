#include "color.hpp"



#include <vector>

using namespace image;



namespace filter::color { 



    // todo maybe extend this function to take a vector (although this implies copy in caller syntax)
    // todo maybe perform sampling of grid pixels not whole image
    RGBA avgColor(const Image<RGBA>& image, const Rect& rect) { 

        
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
        return RGBA(total_r / num_pixels, total_g / num_pixels, total_b / num_pixels);

    }




    void toGrayscale(const Image<RGBA>& src, Image<GRAY>& dest) { 

        dest = Image<GRAY>(src.size());  

        // todo index iterator
        // todo subscript operator [] for image
        for (int i = 0; i < dest.getLinearSize(); i++) { 
            dest.setPixel(i, src.at(i).toGray());
        }
        
    }





    // TODO this will be removed at some point
    void toGrayscale(const Image<RGBA>& src, Image<RGBA>& dest) { 

        dest = Image<RGBA>(src.size());  

        for (int y = 0; y < src.getHeight(); ++y) {
            for (int x = 0; x < src.getWidth(); ++x) {
                const RGBA& pixel = src.at(x, y);

                // Compute luminance (grayscale intensity)
                uint8_t gray = static_cast<uint8_t>(
                    0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b
                );
                RGBA new_pixel(gray);
                dest.setPixel(x, y, new_pixel);
            }
        }
    }
}