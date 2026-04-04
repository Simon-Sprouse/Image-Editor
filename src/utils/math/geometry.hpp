#pragma once

#include "../../data/image/image.hpp"

#include <vector>
#include <array>


namespace Geometry { 

    using image::Point;
    using image::Vec2d;


    inline bool inBoundsRect(const Point& pt, const Point& tl_corner, int dx, int dy) { 
        Point n = pt - tl_corner; // normalized point
        return n.x <= dx && n.y <= dy && n.x >= 0 && n.y >= 0;
    }

   
    Point computeMean(const std::vector<Point>& points);
    std::vector<Point> centerData(const std::vector<Point>& points, const Point& mean);
    std::array<std::array<double, 2>, 2> computeCovarianceMatrix(const std::vector<Point>& points);
    Vec2d computeFirstEigenvector(const std::array<std::array<double, 2>, 2>& cov);
    double pcaLength(const std::vector<Point>& points);




    double euclideanDistance(const Point& a, const Point& b);
    double vectorToAngleDegrees(const Vec2d& vec);
    Vec2d pcaDirection(const std::vector<Point>& points);
    std::vector<Point> filterUniquePoints(const std::vector<Point>& points, double min_distance);

    void sortStrokesPCALength(std::vector<std::vector<Point>>& strokes);

    double pointLineSegmentDistance(const Vec2d& p, const Vec2d& A, const Vec2d& B);
    double norm(const Vec2d& v);


    std::vector<Point> samplePointsSquareBorder(Point center, double theta_deg, double distance_from_center, int num_points);


    std::vector<Point> getPointsInsideSquare(Point center, int size, double angle_deg);



}