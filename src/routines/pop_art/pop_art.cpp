#include "pop_art.hpp"
#include "../../utils/filter/color.hpp"
#include "../../utils/random/random.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector, std::sort, std::cout, std::endl;

namespace pop_art {



void PopArt::loadExistingImage(const Image& img) { 
    original = img.clone();
}

Image PopArt::getCanvas() { 
    return canvas.clone();
}


void PopArt::run() { 
    canvas = original.clone();
    filter::color::toGrayscale(original, gray);

    struct Pixel { 
        Point point;
        Color color;
    };

    struct compGT { 
        // assuming the pixels are both grayscale, compare only r values (reason why Color in imag.hpp not overloaded)
        bool operator()(const Pixel& lhs, const Pixel& rhs) { return lhs.color.r > rhs.color.r; }
    };

    int width = original.getWidth();
    int height = original.getHeight();
    int num_pixels = width * height;

    vector<Pixel> pixels;
    pixels.reserve(num_pixels);
    for (int x = 0; x < width; x++) { 
        for (int y = 0; y < height; y++) { 
            pixels.push_back(Pixel{Point(x, y), gray.at(x, y)});
        }
    }
    sort(pixels.begin(), pixels.end(), compGT());


    vector<Color> colors;
    colors.reserve(params.num_splits);
    for (int i = 0; i < params.num_splits; i++) { 
        colors.push_back(random_gen::randomColor());
    }


    int pixels_per_bin = num_pixels / params.num_splits;
    int bin;
    bin_map = Image(original.size());


    for (int i = 0; i < pixels.size(); i++) { 
        bin = std::min(i / pixels_per_bin, params.num_splits - 1);
        bin_map.setPixel(pixels[i].point, colors[bin]);
    }


    canvas = bin_map.clone();



    // sort all pixels
    // create bins
    // recolor bins



}



}