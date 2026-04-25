#pragma once

#include <stdint.h>
#include <ostream>
#include <vector>

#include "primitives.hpp"


namespace image { 


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
        Color* end() { return ptr_ + width_; }

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


        RegionRowIterator begin() { return RegionRowIterator(start_, dx_, dy_, width_); }
        RegionRowIterator end() { return RegionRowIterator(start_ + (dy_*width_), dx_, 0, width_); }

        RowIterator operator*() { return RowIterator(start_, dx_); }
        RegionRowIterator& operator++() { 
            dy_--;
            start_ += width_;
            return *this;
        }
        bool operator!=(const RegionRowIterator& other) {return start_ != other.start_; };

        RowIterator row() { return RowIterator(start_, dx_); }


};



class ConstRegionRowIterator {
    const Color* start_;
    int dx_;
    int dy_;
    int width_; // for image, not region

    public: 

        ConstRegionRowIterator(const Color* start, int dx, int dy, int width) : start_(start), 
        dx_(dx), dy_(dy), width_(width) {}

        ConstRegionRowIterator begin() const { return ConstRegionRowIterator(start_, dx_, dy_, width_); }
        ConstRegionRowIterator end() const { return ConstRegionRowIterator(start_ + (dy_*width_), dx_, 0, width_); }

        ConstRowIterator operator*() const { return ConstRowIterator(start_, dx_); }
        ConstRegionRowIterator& operator++() { 
            dy_--;
            start_ += width_;
            return *this;
        }
        bool operator!=(const ConstRegionRowIterator& other) const {return start_ != other.start_; };

        ConstRowIterator row() const { return ConstRowIterator(start_, dx_); }
        
};





class RegionIterator { 
    Color* ptr_;
    int dx_;
    int dy_; 
    int width_;
    int x_remaining_;

    public: 
        RegionIterator(Color* ptr, int dx, int dy, int width) : ptr_(ptr),
        dx_(dx), dy_(dy), width_(width), x_remaining_(dx-1) {}

        RegionIterator begin() { return RegionIterator(ptr_, dx_, dy_, width_); }
        RegionIterator end() { 
            Color* end_ptr = ptr_ - (dx_ - x_remaining_ - 1) + (width_ * dy_);
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
                x_remaining_ = dx_ - 1;
                dy_--;
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

    // RegionRowIterator regionRows(Point tl, int dx, int dy);
    // const ConstRegionRowIterator regionRows(const Point& tl, int dx, int dy) const;
    // RegionIterator region(Point tl, int dx, int dy);


    private:


        int width_;
        int height_;
        std::vector<Color> data_;


};







// Stream operator for Image
inline std::ostream& operator<<(std::ostream& os, const Image& image) {
    os << "image[" << image.getWidth() << " x " << image.getHeight() << "]";
    return os;
}









}