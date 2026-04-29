#pragma once

#include "../image/primitives.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace image;

namespace shapes {
    
    struct Rect { 
        Point tl;
        int dx;
        int dy;
    };

    
    // todo overload operators on rect like comp and equals



    struct Axis_Table { 
        vector<int> x_table;
        vector<int> y_table;
    };









    // todo: clean the code, fixed withd, maye used as helper and should live elsewhere
    template <typename T>
    inline void printVector(const std::vector<T>& vec, int max_elements) { 

        int elements = std::min(max_elements, static_cast<int>(vec.size()));
        cout << "vec[";
        for (int i = 0; i < elements - 1; i++) { 
            cout << vec[i] << ", ";
        }
        if (elements) {cout << vec[elements-1];} // print w/ comma
        cout << "](" << elements << " of " << vec.size() << ")";
    }

    template <typename T> 
    inline void printVector(const std::vector<T>& vec) { 
        printVector<T>(vec, 10);
    }


    template <typename T>
    inline void printVectorNewline(const std::vector<T>& vec) { 
        int max_elements = 10;

        int elements = std::min(max_elements, static_cast<int>(vec.size()));
        cout << "vec[" << endl;
        for (int i = 0; i < elements - 1; i++) { 
            cout << "  " << vec[i] << "," << endl;
        }
        if (elements) {cout << "  " << vec[elements-1] << endl;} // print w/ comma
        cout << "](" << elements << " of " << vec.size() << ")" << endl;
    }

    // Overload printing for Rect struct
    inline std::ostream& operator<<(std::ostream& os, const Rect& rect) {
        os 
        << "rect["
        << "tl: " << rect.tl << ", "
        << "dx: " << rect.dx << ", "
        << "dy: " << rect.dy
        << "]";
        return os;
    }

    // Overload printing for Axis_Table struct
    inline std::ostream& operator<<(std::ostream& os, const Axis_Table& ax) { 

        // --- calculate max elements to show ---
        int max_elements = 10;
        int x_elements = std::min(max_elements, static_cast<int>(ax.x_table.size()));
        int y_elements = std::min(max_elements, static_cast<int>(ax.y_table.size()));


        // --- print x table with tab indention ---
        os << "axis table[" << endl;
        os << "  x:[";
        for (int i = 0; i < x_elements - 1; i++) { 
            os << ax.x_table[i] << ", ";
        }
        if (x_elements) {
            os << ax.x_table[x_elements-1]; // no comma last print
        } 
        os << "](" << x_elements << " of " << ax.x_table.size() << ")," << endl;


        // --- print y table with tab indention ---
        os << "  y:[";
        for (int i = 0; i < y_elements - 1; i++) { 
            os << ax.y_table[i] << ", ";
        }
        if (y_elements) {
            os << ax.y_table[y_elements-1];  // no comma last print
        }
        os << "](" << y_elements << " of " << ax.y_table.size() << ")";
        os << endl << "]";


        return os;
    }



}