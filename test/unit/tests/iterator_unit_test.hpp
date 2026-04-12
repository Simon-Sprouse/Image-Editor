#pragma once

#include "../../../src/data/image/image.hpp"

using namespace image;

#include <iostream>
using std::cerr, std::cout, std::endl;

#include <vector>
using std::vector;


#include <string> 
using std::string;

namespace unit_test::iterator { 

    template<typename T>
    bool assertEqual(T lhs, T rhs, string message) { 
        if (!(lhs == rhs)) { 
            cerr << "Failure: " << message << endl;
            cerr << "Expected (" << lhs << " == " << rhs << ")" << endl;
            return false;
        }
        else { 
            cout << "Passed: " << message << endl;
            cout << "Asserted (" << lhs << " == " << rhs << ")" << endl;
            return true;
        }
    }

    template<typename T>
    bool assertEqualVector(vector<T> lhs, vector<T> rhs, string message) { 
        if (!(lhs == rhs)) { 
            cerr << "Failure: " << message << endl;
            cerr << "Expected (vector of size(" << lhs.size() << " == vector of size(" << rhs.size() << "))" << endl;
            return false;
        }
        else { 
            cout << "Passed: " << message << endl;
            cout << "Asserted (vector of size(" << lhs.size() << ") == vector of size(" << rhs.size() << "))" << endl;
            return true;
        }
    }



    void testRegionIterator(Image image);
}