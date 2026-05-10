#pragma once
#include <algorithm>

// todo: find a less ethnic name for this file

namespace image { 

    // todo: move geometric stuff to shapes and expand on color theory here

    struct RGBA { 

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        // === Default Constructor === 
        RGBA() : r(0), g(0), b(0), a(255) {}

        // === uint8 Constructor ===
        RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) 
            : r(red), g(green), b(blue), a(alpha) {}
        explicit RGBA(uint8_t value)
            : RGBA(value, value, value) {}

        // === int Constructor ===
        RGBA(int red, int green, int blue, int alpha = 255) 
            : r(clamp_8b(red)), g(clamp_8b(green)), b(clamp_8b(blue)), a(clamp_8b(alpha)) {}
        explicit RGBA(int value)
            : RGBA(value, value, value) {}

        // === float Constructor ===
        RGBA(float red, float green, float blue, float alpha = 255) 
            : r(clamp_8b(red)), g(clamp_8b(green)), b(clamp_8b(blue)), a(clamp_8b(alpha)) {}
        explicit RGBA(float value)
            : RGBA(value, value, value) {}

        // === double Constructor ===
        RGBA(double red, double green, double blue, double alpha = 255) 
            : r(clamp_8b(red)), g(clamp_8b(green)), b(clamp_8b(blue)), a(clamp_8b(alpha)) {}
        explicit RGBA(double value)
            : RGBA(value, value, value) {}


        bool operator==(const RGBA& other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        bool operator!=(const RGBA& other) const {
            return !(*this == other);
        }

        // todo: figure this out
        // GRAY toGRAY() { 
        //     return RGBA2GRAY(*this);
        // }


        private:

            // todo more elegant solution here: limits, widening, templatizing
            static constexpr uint8_t clamp_8b(int value) { 
                return static_cast<uint8_t>(std::clamp(value, 0, 255));
            }


    };
    static_assert(sizeof(RGBA) == 4);


    struct HSV { 

        uint16_t h;
        uint8_t s;
        uint8_t v;

        HSV() : h(0), s(0), v(0) {}

        HSV(uint16_t hue) 
            : h(hue), s(255), v(255) {}

        HSV(uint16_t hue, uint8_t saturation, uint8_t value)
            : h(hue), s(saturation), v(value) {}


        // todo need way more of these

    };
    static_assert(sizeof(HSV) == 4);


    struct GRAY { 
        uint8_t v;

        GRAY() : v(0) {}
        GRAY(uint8_t value) : v(value) {}

    };
    static_assert(sizeof(GRAY) == 1);


    // todo MASK type






    inline GRAY RGBA2GRAY(const RGBA& px) {

        // todo clamp should solve this
        uint8_t luminance = static_cast<uint8_t>(0.299 * px.r + 0.587 * px.g + 0.114 * px.b);
        return GRAY(luminance);
    }





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

    // Stream operator for RGBA
    inline std::ostream& operator<<(std::ostream& os, const RGBA& color) {

        os << "rgba[" << static_cast<int>(color.r) << ", "
                    << static_cast<int>(color.g) << ", "
                    << static_cast<int>(color.b) << ", "
                    << static_cast<int>(color.a) << "]";


        return os;
    }


    // Stream operator for HSV
    inline std::ostream& operator<<(std::ostream& os, const HSV& color) {

        os << "hsv[" << static_cast<int>(color.h) << ", "
                    << static_cast<int>(color.s) << ", "
                    << static_cast<int>(color.v) << "]";


        return os;
    }

    // Stream operator for GRAY
    inline std::ostream& operator<<(std::ostream& os, const GRAY& color) {

        os << "gray[" << static_cast<int>(color.v) << "]";

        return os;
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