#pragma once

#include "../../data/image/image.hpp"

// #include <opencv2/opencv.hpp>
#include <string>

using namespace image;


namespace Graphics { 





    void drawLine(Image<RGB>& image, const Point& point_a, const Point& point_b, int thickness, const RGB& color);
    void drawArrow(Image<RGB>& image, const Point& center, int length, int thickness, double angle_deg, const RGB& color);

    void drawFilledPolygon(Image<RGB>& image, const std::vector<Point>& polygon, const RGB& color);
    void drawSquare(Image<RGB>& image, const Point& center, double size, double angle_deg, const RGB& color, int border_width);

    void drawStroke(Image<RGB>& image, const std::vector<Point>& strokes, const RGB& color);
    void drawStrokesRandomColor(Image<RGB>& image, const std::vector<std::vector<Point>>& strokes);


    // TODO this will take some time
    // void drawText(Image& image, const Point& center, double size, double angle_deg, const RGB& color);



}

