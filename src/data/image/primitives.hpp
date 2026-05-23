#pragma once
#include <algorithm>
#include <array>
#include <iostream>

using std::cout, std::endl;

// todo: find a less ethnic name for this file

namespace image { 

    // todo: move geometric stuff to shapes and expand on color theory here

   



    struct Point { 

        int x;
        int y;


        Point() : x(0), y(0) {}
        Point(int x, int y) : x(x), y(y) {}
        Point(float x, float y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}
        Point(double x, double y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}


        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Point& other) const {
            return !(*this == other);
        }

    };

    // Subtraction operator
    inline Point operator-(const Point& a, const Point& b) {
        return Point(a.x - b.x, a.y - b.y);
    }



    struct Vec2d {
        double x;
        double y;

        Vec2d() : x(0), y(0) {}
        Vec2d(double x_, double y_) : x(x_), y(y_) {}

        // Constructor from Point
        Vec2d(const Point& p) : x(static_cast<double>(p.x)), y(static_cast<double>(p.y)) {}

        double dot(const Vec2d& other) const {
            return x * other.x + y * other.y;
        };


    };

    // Subtraction operator
    inline Vec2d operator+(const Vec2d& a, const Vec2d& b) {
        return Vec2d(a.x + b.x, a.y + b.y);
    }

    inline Vec2d operator-(const Vec2d& a, const Vec2d& b) {
        return Vec2d(a.x - b.x, a.y - b.y);
    }

    // TODO finish all arithmetic
    inline Vec2d operator*(const Vec2d& v, double scalar) {
        return Vec2d(v.x * scalar, v.y * scalar);
    }

    inline Vec2d operator/(const Vec2d& v, double scalar) {
        return Vec2d(v.x / scalar, v.y / scalar);
    }




    struct Size { 

        int width;
        int height;


        Size() : width(0), height(0) {}
        Size(int w, int h) : width(w), height(h) {}

        bool operator==(const Size& other) const {
            return width == other.width && height == other.height;
        }

        bool operator!=(const Size& other) const {
            return !(*this == other);
        }

        std::string toString() const;
        

    };

    inline Size operator*(const Size& s, double scalar) {
        return Size(s.width * scalar, s.height * scalar);
    }




    // Stream operator for Size
    inline std::ostream& operator<<(std::ostream& os, const Size& s) {
        return os << "size[" << s.width << " x " << s.height << "]";
    }

    inline std::string Size::toString() const {
        return std::to_string(width) + "," + std::to_string(height);
    }

    


    // Stream operator for Point
    inline std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "point[" << point.x << ", " << point.y << "]";
        return os;
    }

    // Stream operator for Vec2d
    inline std::ostream& operator<<(std::ostream& os, const Vec2d& vec) {
        os << "vec2d[" << vec.x << ", " << vec.y << "]";
        return os;
    }






}