#pragma once

#include <stdint.h>
#include <ostream>
#include <vector>

#include "primitives.hpp"
#include "iterator.hpp"
#include "../shapes/shapes.hpp"

namespace image { 

using shapes::Rect;



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
    RegionRowIterator regionRows(const Rect& rect);
    const ConstRegionRowIterator regionRows(const Rect& rect) const;
    RegionIterator region(const Rect& rect);

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