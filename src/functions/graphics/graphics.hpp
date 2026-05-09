#pragma once

#include "../../data/image/image.hpp"

// #include <opencv2/opencv.hpp>
#include <string>

using namespace image;


namespace Graphics { 





    void drawLine(Image<RGBA>& image, const Point& point_a, const Point& point_b, int thickness, const RGBA& color);
    void drawArrow(Image<RGBA>& image, const Point& center, int length, int thickness, double angle_deg, const RGBA& color);

    void drawFilledPolygon(Image<RGBA>& image, const std::vector<Point>& polygon, const RGBA& color);
    void drawSquare(Image<RGBA>& image, const Point& center, double size, double angle_deg, const RGBA& color, int border_width);

    void drawStroke(Image<RGBA>& image, const std::vector<Point>& strokes, const RGBA& color);
    void drawStrokesRandomColor(Image<RGBA>& image, const std::vector<std::vector<Point>>& strokes);


    // TODO this will take some time
    // void drawText(Image& image, const Point& center, double size, double angle_deg, const RGBA& color);



}

