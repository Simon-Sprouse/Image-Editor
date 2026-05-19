#pragma once

#include <stdint.h>
#include <ostream>
#include <vector>

#include "primitives.hpp"
#include "iterator.hpp"
#include "../shapes/shapes.hpp"

namespace image { 

using shapes::Rect;


template <typename Px>
class Image {


    public: 


    // Default constructor
    Image();

    // Param constructors
    Image(int width, int height);
    Image(int width, int height, const Px& fill);
    Image(Size size);
    Image(Size size, const Px& fill);
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

    Px& at(int index);
    const Px& at(int index) const;
    Px& at(int x, int y);
    const Px& at(int x, int y) const;
    Px& at(Point pt);
    const Px& at(Point pt) const;
    Size size() const;
    int linearSize() const;
    int getHeight() const;
    int getWidth() const;
    uint8_t* rawData();
    const uint8_t* rawData() const;
    size_t rawDataBytesSize();
    const size_t rawDataBytesSize() const;
    void setPixel(int index, const Px& color);
    void setPixel(int x, int y, const Px& color);
    void setPixel(const Point& pt, const Px& color);
    bool empty() const;
    void fill(const Px& color);
    Image clone() const;
    bool inBounds(int x, int y) const;

    bool operator==(const Image& other) const;
    bool operator!=(const Image& other) const;

    int getLinearIndex(Point pt) const;
    int getLinearIndex(int x, int y) const;

    // TODO think about literal iterator overload
    // TODO cbegin() and cend() ? cdata()?
    Px* data() { return data_.data(); }
    const Px* data() const { return data_.data(); }
    Px* begin() { return data(); }
    const Px* begin() const { return data(); }
    Px* end() { return data() + data_.size(); }
    const Px* end() const { return data() + data_.size(); }
    
    Px* rowPtr(int y);
    const Px* rowPtr(int y) const;
    RowIterator row(int y);
    // const ConstRowIterator row(int y); // TODO I don't need this right? 
    RegionRowIterator regionRows(const Rect& rect);
    const ConstRegionRowIterator regionRows(const Rect& rect) const;
    RegionIterator region(const Rect& rect);

    // RegionRowIterator regionRows(Point tl, int dx, int dy);
    // const ConstRegionRowIterator regionRows(const Point& tl, int dx, int dy) const;
    // RegionIterator region(Point tl, int dx, int dy);


    private:


        int width_;
        int height_;
        std::vector<Px> data_;


};





// Default constructor
template <typename Px>
Image<Px>::Image() : width_(0), height_(0) {}

// Param constructors
template <typename Px>
Image<Px>::Image(int width, int height)
    : width_(width), height_(height), data_(std::vector<Px>(width_* height_, Px())) {}

template <typename Px>
Image<Px>::Image(int width, int height, const Px& fill)
    : width_(width), height_(height), data_(std::vector<Px>(width_* height_, fill)) {}

template <typename Px>
Image<Px>::Image(Size size)
    : width_(size.width), height_(size.height), data_(std::vector<Px>(size.width * size.height, Px())) {}

template <typename Px>
Image<Px>::Image(Size size, const Px& fill)
    : width_(size.width), height_(size.height), data_(std::vector<Px>(size.width * size.height, fill)) {}

// Copy constructor
template <typename Px>
Image<Px>::Image(const Image<Px>& other) 
    : width_(other.width_), height_(other.height_), data_(other.data_) {}

// Move constructor
template <typename Px>
Image<Px>::Image(Image<Px>&& other) noexcept 
    : width_(other.width_), height_(other.height_)  {
    data_ = std::move(other.data_);
    other.width_ = 0;
    other.height_ = 0;
}

// Copy assignment
template <typename Px>
Image<Px>& Image<Px>::operator=(const Image<Px>& other) {
    if (this != &other) { 
        data_.clear();

        width_ = other.width_;
        height_ = other.height_;
        data_ = other.data_;
    }
    return *this;
}

// Move assignment
template <typename Px>
Image<Px>& Image<Px>::operator=(Image<Px>&& other) noexcept {
    if (this != &other) { 
        data_.clear();

        width_ = other.width_;
        height_ = other.height_;
        data_ = std::move(other.data_);

        other.width_ = 0;
        other.height_ = 0;
    }
    return *this;
}

// Destructor
template <typename Px>
Image<Px>::~Image() {}


template <typename Px>
int Image<Px>::getLinearIndex(Point pt) const { 
    return getLinearIndex(pt.x, pt.y);
}

template <typename Px>
int Image<Px>::getLinearIndex(int x, int y) const { 
    return y * width_ + x;
}

template <typename Px>
Px& Image<Px>::at(int index) { 
    return data_[index];
}

template <typename Px>
const Px& Image<Px>::at(int index) const {
    return data_[index];
}

template <typename Px>
Px& Image<Px>::at(int x, int y) {
    return data_[getLinearIndex(x, y)];
}

template <typename Px>
const Px& Image<Px>::at(int x, int y) const {
    return data_[getLinearIndex(x, y)];
}

template <typename Px>
Px& Image<Px>::at(Point pt) {
    return data_[getLinearIndex(pt.x, pt.y)];
}

template <typename Px>
const Px& Image<Px>::at(Point pt) const {
    return data_[getLinearIndex(pt.x, pt.y)];
}

template <typename Px>
int Image<Px>::linearSize() const { 
    return height_ * width_;
}

template <typename Px>
Size Image<Px>::size() const { 
    return Size(width_, height_);
}

template <typename Px>
int Image<Px>::getHeight() const {
    return height_;
}

template <typename Px>
int Image<Px>::getWidth() const {
    return width_;
}

template <typename Px>
bool Image<Px>::operator==(const Image<Px>& other) const {
    if (this->size() != other.size()) return false;

    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            if (this->at(x, y) != other.at(x, y))
                return false;
        }
    }
    return true;
}

template <typename Px>
bool Image<Px>::operator!=(const Image<Px>& other) const {
    return !(*this==other);
}


template <typename Px>
uint8_t* Image<Px>::rawData() {
    return reinterpret_cast<uint8_t*>(data_.data());
}

template <typename Px>
const uint8_t* Image<Px>::rawData() const {
    return reinterpret_cast<const uint8_t*>(data_.data());
}

template <typename Px>
size_t Image<Px>::rawDataBytesSize() { 
    return data_.size() * sizeof(Px);
}

template <typename Px>
const size_t Image<Px>::rawDataBytesSize() const { 
    return data_.size() * sizeof(Px);
}

template <typename Px>
void Image<Px>::setPixel(int index, const Px& color) { 
    data_.at(index) = color;
}

template <typename Px>
void Image<Px>::setPixel(int x, int y, const Px& color) {
    setPixel(getLinearIndex(x, y), color);
}

template <typename Px>
void Image<Px>::setPixel(const Point& pt, const Px& color) { 
    setPixel(getLinearIndex(pt.x, pt.y), color);
}

template <typename Px>
bool Image<Px>::empty() const { 
    return data_.empty();
}

template <typename Px>
void Image<Px>::fill(const Px& color) {
    std::fill(data_.begin(), data_.end(), color);
}

template <typename Px>
Image<Px> Image<Px>::clone() const {
    Image<Px> copy(width_, height_);
    copy.data_ = data_; // std::vector assignment performs a deep copy
    return copy;
}

template <typename Px>
bool Image<Px>::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < getWidth() && y < getHeight();
}

template <typename Px>
Px* Image<Px>::rowPtr(int y) { 
    return data() + (y * width_);
}

template <typename Px>
const Px* Image<Px>::rowPtr(int y) const {
    return data() + (y * width_);
}

template <typename Px>
RowIterator Image<Px>::row(int y) { 
    return RowIterator(rowPtr(y), width_);
}

template <typename Px>
RegionRowIterator Image<Px>::regionRows(const Rect& rect) { 
    Px* start = data() + getLinearIndex(rect.tl);
    return RegionRowIterator(start, rect.dx, rect.dy, width_);
}

template <typename Px>
const ConstRegionRowIterator Image<Px>::regionRows(const Rect& rect) const { 
    const Px* start = data() + getLinearIndex(rect.tl);
    return ConstRegionRowIterator(start, rect.dx, rect.dy, width_);
}

template <typename Px>
RegionIterator Image<Px>::region(const Rect& rect) { 
    Px* start = data() + getLinearIndex(rect.tl);
    return RegionIterator(start, rect.dx, rect.dy, width_);
}







// Stream operator for Image
template <typename Px>
inline std::ostream& operator<<(std::ostream& os, const Image<Px>& image) {
    os << "image[" << image.getWidth() << " x " << image.getHeight() << "]";
    return os;
}





Image<HSV> toHSV(const Image<RGBA>& original);
Image<RGBA> toRGBA(const Image<HSV>& original);
Image<GRAY> toGRAY(const Image<RGBA>& original);


void HSV2RGBA_simd(HSV* ptr, RGBA* dest);
Image<RGBA> toRGBA_simd(Image<HSV>& original); // todo this should be const

void RGBA2HSV_simd(RGBA* src, HSV* dest);
Image<HSV> toHSV_simd(Image<RGBA>& original);






}