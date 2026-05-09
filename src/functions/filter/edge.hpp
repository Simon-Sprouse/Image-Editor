#pragma once 

#include <vector>

#include "../../data/image/image.hpp"

using namespace image;


namespace filter::edge { 
    void sobelFilter(const Image<RGBA>& src, Image<RGBA>& dest_grad_x, Image<RGBA>& dest_grad_y);
    void visualizeSobel(const Image<RGBA>& src_grad_x, const Image<RGBA>& src_grad_y, Image<RGBA>& dest);

    void cannyFilter(Image<RGBA>& src, Image<RGBA>& dest, int canny_threshold_1, int canny_threshold_2);
    void sobelFilterRaw(const Image<RGBA>& src, std::vector<int>& gradX, std::vector<int>& gradY);
    
    void findContours(const Image<RGBA>& src_binary, std::vector<std::vector<Point>>& contours);
    int  divideIntoStrokes(const std::vector<std::vector<Point>>& cv_contours, 
        std::vector<std::vector<Point>>& segment_points, 
        Size image_size, 
        int segment_angle_window, 
        double max_segment_angle_rad, 
        int min_segment_length);


    // TODO separate logic for distance field and gradient of distance field
    std::vector<float> computeDistanceField(const Image<RGBA>& strokes_img_source);
    Image<RGBA> floatMapToGrayscaleImage(const std::vector<float>& data, Size size);
    void computeSobelGradients(const std::vector<float>& distance_map, Size size, std::vector<float>& grad_x, std::vector<float>& grad_y);
}