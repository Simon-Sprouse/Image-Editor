#include "iterator_unit_test.hpp"

#include <iostream>

using std::cout, std::endl;

namespace unit_test::iterator {
    void testIterator(Image& image) { 
        cout << "hello from iterator unit test" << endl;
        cout << "image size: " << image.size() << endl;
    }
}