#include "pop_art.hpp"
#include "../../functions/filter/color.hpp"
#include "../../functions/random/random.hpp"

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


// TODO: Downsample to find bin map? 

void PopArt::run() { 

    // grayscale image
    filter::color::toGrayscale(original, gray);

    // create histogram of grayscale values O(n)
    vector<int> value_counts_histogram(256, 0);
    int num_pixels = original.getFlatSize();
    for (int i = 0; i < num_pixels; i++) { 
        value_counts_histogram[gray.at(i).r] += 1;
    }

    // walk through historgram and create bins O(256)
    int num_bins = params.num_splits;
    int pixels_per_bin = num_pixels / num_bins;
    vector<int> bin_id_for_value(256, 0); // x[grayscale value] = bin_id
    int num_pixels_current_bin = 0;
    int current_bin_id = 0;
    for (int value = 0; value < 256; value++) { 
        if (num_pixels_current_bin > pixels_per_bin) { 
            num_pixels_current_bin = 0;
            current_bin_id += 1;
        }
        bin_id_for_value[value] = std::min(current_bin_id, num_bins - 1);
        num_pixels_current_bin += value_counts_histogram[value];
    }

    // generate random colors
    vector<Color> colors = random_gen::randomColors(num_bins);

    // map all possible grayscale values to new colors
    vector<Color> new_color_for_value(256); 
    for (int value = 0; value < 256; value++) { 
        new_color_for_value[value] = colors[bin_id_for_value[value]];
    }

    // recolor image using map O(n)
    canvas = Image(original.size());
    for (int i = 0; i < num_pixels; i++) { 
        canvas.setPixel(i, new_color_for_value[gray.at(i).r]);
    }   



}


void PopArt::findBins_() { 

    // grayscale image
    filter::color::toGrayscale(original, gray);

    // count number of pixels for each grayscale value
    vector<int> value_counts_histogram(256, 0);
    int num_pixels = original.getFlatSize();
    for (int i = 0; i < num_pixels; i++) { 
        value_counts_histogram[gray.at(i).r] += 1;
    }

    // walk through grayscale values histogram and assign bin_id to each value
    int num_bins = params.num_splits;
    int pixels_per_bin = num_pixels / num_bins;
    vector<int> bin_id_for_value(256, 0); // key: color value, value: bin_id eg: x[(244)] = id(5)
    int num_pixels_current_bin = 0;
    int current_bin_id = 0;
    for (int value = 0; value < 256; value++) { 
        if (num_pixels_current_bin > pixels_per_bin) { 
            num_pixels_current_bin = 0;
            current_bin_id += 1;
        }
        bin_id_for_value[value] = std::min(current_bin_id, num_bins - 1);
        num_pixels_current_bin += value_counts_histogram[value];
    }

    // set all pixels in bin_map to store (bin_id, bin_id, bin_id) as color
    bin_map = Image(original.size());
    int bin_id_for_pixel;
    for (int i = 0; i < num_pixels; i++) { 
        bin_id_for_pixel = bin_id_for_value[gray.at(i).r];
        bin_map.setPixel(i, Color(bin_id_for_pixel));
    }
}

void PopArt::runPersistent() {

    if (bin_map.empty()) { 
        findBins_();
    }

    // collect vector of random colors
    vector<Color> colors = random_gen::randomColors(params.num_splits); 
    
    // recolor image
    // extract bin_id from each pixel and recolor pixel based on bin_id
    canvas = Image(original.size());
    for (int i = 0; i < bin_map.getFlatSize(); i++) { 
        canvas.setPixel(i, colors[bin_map.at(i).r]);
    }   

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
    int num_bins = params.num_splits;

    vector<Pixel> pixels;
    pixels.reserve(num_pixels);
    for (int x = 0; x < width; x++) { 
        for (int y = 0; y < height; y++) { 
            pixels.push_back(Pixel{Point(x, y), gray.at(x, y)});
        }
    }
    sort(pixels.begin(), pixels.end(), compGT());


    vector<Color> colors;
    colors.reserve(num_bins);
    for (int i = 0; i < num_bins; i++) { 
        colors.push_back(random_gen::randomColor());
    }


    int pixels_per_bin = num_pixels / num_bins;
    int bin;
    bin_map = Image(original.size());


    for (int i = 0; i < pixels.size(); i++) { 
        bin = std::min(i / pixels_per_bin, num_bins - 1);
        bin_map.setPixel(pixels[i].point, colors[bin]);
    }


    canvas = bin_map.clone();



    // sort all pixels
    // create bins
    // recolor bins



}



}