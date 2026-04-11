#pragma once

#include <stdint.h>
#include <ostream>
#include <vector>

namespace image { 

struct Color { 

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color() : r(0), g(0), b(0), a(255) {}

    explicit Color(uint8_t value) 
        : r(value), g(value), b(value), a(255) {}
    Color(uint8_t red, uint8_t green, uint8_t blue) 
        : r(red), g(green), b(blue), a(255) {}
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) 
        : r(red), g(green), b(blue), a(alpha) {}

    explicit Color(int value) 
        : r(clampToByte(value)), g(clampToByte(value)), b(clampToByte(value)), a(255) {}
    Color(int red, int green, int blue) 
        : r(clampToByte(red)), g(clampToByte(green)), b(clampToByte(blue)), a(255) {}
    Color(int red, int green, int blue, int alpha) 
        : r(clampToByte(red)), g(clampToByte(green)), b(clampToByte(blue)), a(clampToByte(alpha)) {}

    explicit Color(float value) 
        : r(clampToByte(static_cast<int>(value))), g(clampToByte(static_cast<int>(value))), 
          b(clampToByte(static_cast<int>(value))), a(255) {}
    Color(float red, float green, float blue) 
        : r(clampToByte(static_cast<int>(red))), g(clampToByte(static_cast<int>(green))), 
          b(clampToByte(static_cast<int>(blue))), a(255) {}
    Color(float red, float green, float blue, float alpha) 
        : r(clampToByte(static_cast<int>(red))), g(clampToByte(static_cast<int>(green))), 
          b(clampToByte(static_cast<int>(blue))), a(clampToByte(static_cast<int>(alpha))) {}

    explicit Color(double value) 
        : r(clampToByte(static_cast<int>(value))), g(clampToByte(static_cast<int>(value))), 
          b(clampToByte(static_cast<int>(value))), a(255) {}
    Color(double red, double green, double blue) 
        : r(clampToByte(static_cast<int>(red))), g(clampToByte(static_cast<int>(green))), 
          b(clampToByte(static_cast<int>(blue))), a(255) {}
    Color(double red, double green, double blue, double alpha) 
        : r(clampToByte(static_cast<int>(red))), g(clampToByte(static_cast<int>(green))), 
          b(clampToByte(static_cast<int>(blue))), a(clampToByte(static_cast<int>(alpha))) {}
 

    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }


    

    private:

        static constexpr uint8_t clampToByte(int value) { 
            if (value < 0) return 0;
            else if (value > 255) return 255;
            return static_cast<uint8_t>(value);
        }

};



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








// The rowPtr function already returns a pointer to the first element in row
// This iterator must expand beyond that existing functionality
// there are two main advantages that justify this class
// 1. This iterator tracks width - therefore it can implement begin() and end() for range iteration
// 2. This iterator allows a direct fill() method enabling image.row(y).fill(color);
class RowIterator { 
    Color* ptr_;
    int width_;

    public:
        RowIterator(Color* ptr, int width) : ptr_(ptr), width_(width) {}

        Color* begin() { return ptr_; }
        const Color* begin() const { return ptr_; } // todo do we need these const methods? 
        Color* end() { return ptr_ + width_; }
        const Color* end() const { return ptr_ + width_; }

        Color& operator[](int x) { return ptr_[x]; }
        const Color& operator[](int x) const { return ptr_[x]; }
        Color* data() { return ptr_; }
        int size() { return width_; }
        void fill(const Color& color) { std::fill_n(ptr_, width_, color); }

};


// Typically iterators are templatized to allow the pointer type to change. 
// We will templatize the iterator later when we need to support other pixel types
// Aside the point -- this templating trick can be used to achieve a const iterator
// by passing in a const pointer as a template and writing two simple typedefs. 
// Ai suggested this strongly
// Here's the catch:
// Our base RowIterator class supports a custom method fill() which modifies the data
// A templated iterator with const pointer but also a fill() method is NINCOMPOOP CODE
// Thank you. :)
class ConstRowIterator { 
    const Color* ptr_;
    int width_;

    public:
        ConstRowIterator(const Color* ptr, int width) : ptr_(ptr), width_(width) {}

        const Color* begin() const { return ptr_; }
        const Color* end() const { return ptr_ + width_; }

        const Color& operator[](int x) const { return ptr_[x]; }
        const Color* data() const { return ptr_; }
        int size() const { return width_; }

};








class RegionRowIterator {
    Color* start_;
    int dx_;
    int dy_;
    int width_; // for image, not region

    public: 

        RegionRowIterator(Color* start, int dx, int dy, int width) : start_(start), 
        dx_(dx), dy_(dy), width_(width) {}


        RowIterator operator*() { return RowIterator(start_, dx_); }
        RowIterator row() { return RowIterator(start_, dx_); }
        RegionRowIterator& operator++() { 
            dy_--;
            start_ += width_;
            return *this;
        }
        bool operator!=(const RegionRowIterator& other) {return start_ != other.start_; };

        RegionRowIterator begin() { return RegionRowIterator(start_, dx_, dy_, width_); }
        RegionRowIterator end() { return RegionRowIterator(start_ + (dy_*width_), dx_, 0, width_); }

};



class ConstRegionRowIterator {
    const Color* start_;
    int dx_;
    int dy_;
    int width_; // for image, not region

    public: 

        ConstRegionRowIterator(const Color* start, int dx, int dy, int width) : start_(start), 
        dx_(dx), dy_(dy), width_(width) {}


        ConstRowIterator operator*() const { return ConstRowIterator(start_, dx_); }
        ConstRowIterator row() const { return ConstRowIterator(start_, dx_); }
        ConstRegionRowIterator& operator++() { 
            dy_--;
            start_ += width_;
            return *this;
        }
        bool operator!=(const ConstRegionRowIterator& other) const {return start_ != other.start_; };

        ConstRegionRowIterator begin() const { return ConstRegionRowIterator(start_, dx_, dy_, width_); }
        ConstRegionRowIterator end() const { return ConstRegionRowIterator(start_ + (dy_*width_), dx_, 0, width_); }

};





class RegionIterator { 
    Color* ptr_;
    int dx_;
    int y_remaining_; // called remaining because it experiences decrement
    int width_;
    int x_remaining_;

    public: 
        RegionIterator(Color* ptr, int dx, int dy, int width) : ptr_(ptr),
        dx_(dx), y_remaining_(dy-1), width_(width), x_remaining_(dx-1) {}

        RegionIterator begin() { return RegionIterator(ptr_, dx_, y_remaining_, width_); }
        RegionIterator end() { 
            Color* end_ptr = ptr_ + x_remaining_ + 1 + (width_ * y_remaining_);
            return RegionIterator(end_ptr, dx_, 0, width_); 
        }
        Color& operator*() { return *ptr_; }

        RegionIterator& operator++() { 
            if (x_remaining_) { 
                ptr_++;
                x_remaining_--;
            }
            else { 
                ptr_ += width_ - dx_ + 1;
                x_remaining_ = dx_;
                y_remaining_--;
            }
            return *this;
        }
        bool operator!=(const RegionIterator& other) { return ptr_ != other.ptr_; }
};













class Image {


    public: 


    // Default constructor
    Image();

    // Param constructors
    Image(int width, int height);
    Image(int width, int height, const Color& fill);
    Image(Size size);
    Image(Size size, const Color& fill);
    Image(Size size, const std::vector<float>& vec);

    // Copy constructor
    Image(const Image& other);

    // Move constructor
    Image(Image&& other) noexcept;

    // Copy assignment
    Image& operator=(const Image& other);

    // Move assignment
    Image& operator=(Image&& other) noexcept;

    // Destructor
    ~Image();

    Color& at(int index);
    const Color& at(int index) const;
    Color& at(int x, int y);
    const Color& at(int x, int y) const;
    Color& at(Point pt);
    const Color& at(Point pt) const;
    Size size() const;
    int getFlatSize() const;
    int getHeight() const;
    int getWidth() const;
    uint8_t* rawData();
    const uint8_t* rawData() const;
    size_t rawDataBytesSize();
    const size_t rawDataBytesSize() const;
    void setPixel(int index, const Color& color);
    void setPixel(int x, int y, const Color& color);
    void setPixel(const Point& pt, const Color& color);
    bool empty() const;
    void fill(const Color& color);
    Image clone() const;
    bool inBounds(int x, int y) const;

    bool operator==(const Image& other) const;
    bool operator!=(const Image& other) const;

    int getLinearIndex(Point pt) const;
    int getLinearIndex(int x, int y) const;

    // TODO think about literal iterator overload
    // TODO cbegin() and cend() ? cdata()?
    Color* data() { return data_.data(); }
    const Color* data() const { return data_.data(); }
    Color* begin() { return data(); }
    const Color* begin() const { return data(); }
    Color* end() { return data() + data_.size(); }
    const Color* end() const { return data() + data_.size(); }
    
    Color* rowPtr(int y);
    const Color* rowPtr(int y) const;
    RowIterator row(int y);
    // const ConstRowIterator row(int y); // TODO I don't need this right? 
    RegionRowIterator regionRows(Point tl, int dx, int dy);
    const ConstRegionRowIterator regionRows(const Point& tl, int dx, int dy) const;
    RegionIterator region(Point tl, int dx, int dy);



    private:

        


        int width_;
        int height_;
        std::vector<Color> data_;


};






// Stream operator for Size
inline std::ostream& operator<<(std::ostream& os, const Size& s) {
    return os << "size[" << s.width << " x " << s.height << "]";
}

inline std::string Size::toString() const {
    return std::to_string(width) + "," + std::to_string(height);
}

// Stream operator for Color
inline std::ostream& operator<<(std::ostream& os, const Color& color) {

    os << "rgba[" << static_cast<int>(color.r) << ", "
                << static_cast<int>(color.g) << ", "
                << static_cast<int>(color.b) << ", "
                << static_cast<int>(color.a) << "]";


    return os;
}

// Stream operator for Point
inline std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "point[" << point.x << ", " << point.y << "]";
    return os;
}

// Stream operator for Point
inline std::ostream& operator<<(std::ostream& os, const Vec2d& vec) {
    os << "vec2d[" << vec.x << ", " << vec.y << "]";
    return os;
}


// Stream operator for Image
inline std::ostream& operator<<(std::ostream& os, const Image& image) {
    os << "image[" << image.getWidth() << " x " << image.getHeight() << "]";
    return os;
}









}