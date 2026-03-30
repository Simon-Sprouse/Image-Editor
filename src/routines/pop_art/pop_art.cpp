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


    // grayscale image
    // flatten image with loop and make histogram of pixels (store this?)
    // run through historgram and add bin cutoff points to parallel array
    // create color table mapped to bin ids
    // flatten image and recolor

    filter::color::toGrayscale(original, gray);


    vector<int> value_counts_histogram(256, 0);
    int num_pixels = original.getFlatSize();
    for (int i = 0; i < num_pixels; i++) { 
        value_counts_histogram[gray.at(i).r] += 1;
    }


    int pixels_per_bin = num_pixels / params.num_splits;
    vector<int> bin_id_for_value(256, 0); // key: color value, value: bin_id eg: x[(244)] = id(5)
    int num_pixels_current_bin = 0;
    int current_bin_id = 0;
    for (int value = 0; value < 256; value++) { 
        if (num_pixels_current_bin <= pixels_per_bin) { 
            bin_id_for_value[value] = current_bin_id;
        }
        else { 
            num_pixels_current_bin = 0;
            current_bin_id += 1;
        }
        num_pixels_current_bin += value_counts_histogram[value];
    }

    vector<Color> colors; // TODO random vector of colors from random library
    colors.reserve(params.num_splits);
    for (int i = 0; i < params.num_splits; i++) { 
        colors.push_back(random_gen::randomColor());
    }   

    vector<Color> old_value_new_color; // (key) gray value : (value) new color
    old_value_new_color.reserve(256);
    for (int bin_id : bin_id_for_value) { 
        old_value_new_color.push_back(colors[bin_id]);
    }


    canvas = Image(original.size());
    for (int i = 0; i < num_pixels; i++) { 
        canvas.setPixel(i, old_value_new_color[gray.at(i).r]);
    }   








    // note: should I create hist mapped color array to do lookup color -> new color? 
    //       or should I do color -> bin_id -> new color? 











}


void PopArt::runSlow() { 
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