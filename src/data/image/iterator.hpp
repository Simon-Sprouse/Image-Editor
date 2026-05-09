#pragma once

#include "primitives.hpp"

namespace image { 

    // The rowPtr function already returns a pointer to the first element in row
    // This iterator must expand beyond that existing functionality
    // there are two main advantages that justify this class
    // 1. This iterator tracks width - therefore it can implement begin() and end() for range iteration
    // 2. This iterator allows a direct fill() method enabling image.row(y).fill(color);
    class RowIterator { 
        RGBA* ptr_;
        int width_;

        public:
            RowIterator(RGBA* ptr, int width) : ptr_(ptr), width_(width) {}

            RGBA* begin() { return ptr_; }
            RGBA* end() { return ptr_ + width_; }

            RGBA& operator[](int x) { return ptr_[x]; }
            const RGBA& operator[](int x) const { return ptr_[x]; }
            RGBA* data() { return ptr_; }
            int size() { return width_; }
            void fill(const RGBA& color) { std::fill_n(ptr_, width_, color); }

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
        const RGBA* ptr_;
        int width_;

        public:
            ConstRowIterator(const RGBA* ptr, int width) : ptr_(ptr), width_(width) {}

            const RGBA* begin() const { return ptr_; }
            const RGBA* end() const { return ptr_ + width_; }

            const RGBA& operator[](int x) const { return ptr_[x]; }
            const RGBA* data() const { return ptr_; }
            int size() const { return width_; }

    };








    class RegionRowIterator {
        RGBA* start_; // todo: color theory -- should RGBA* be the data type in image? Should image be SoA per each channel? 
        int dx_;
        int dy_;
        int width_; // for image, not region

        public: 

            RegionRowIterator(RGBA* start, int dx, int dy, int width) : start_(start), 
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
        const RGBA* start_;
        int dx_;
        int dy_;
        int width_; // for image, not region

        public: 

            ConstRegionRowIterator(const RGBA* start, int dx, int dy, int width) : start_(start), 
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




    // this is a footgun likely
    class RegionIterator { 
        RGBA* ptr_;
        int dx_;
        int dy_; 
        int width_;
        int x_remaining_;

        public: 
            RegionIterator(RGBA* ptr, int dx, int dy, int width) : ptr_(ptr),
            dx_(dx), dy_(dy), width_(width), x_remaining_(dx-1) {}

            RegionIterator begin() { return RegionIterator(ptr_, dx_, dy_, width_); }
            RegionIterator end() { 
                RGBA* end_ptr = ptr_ - (dx_ - x_remaining_ - 1) + (width_ * dy_);
                return RegionIterator(end_ptr, dx_, 0, width_); 
            }
            RGBA& operator*() { return *ptr_; }

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




}