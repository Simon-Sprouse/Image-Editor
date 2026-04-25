#include "iterator_examples.hpp"
#include "../../src/data/image/image.hpp"
#include "../../src/data/image/io.hpp"
#include "../../src/data/shapes/shapes.hpp"

#include <iostream>


using image::Image, image::Color, image::Point;
using std::cout, std::endl;

namespace workbench { 


    void runIterator(string image_path, Logger logger) { 

        using image::RegionIterator, image::RegionRowIterator, image::RowIterator;

        cout << "running testIterators" << endl;

        Image image = image::io::loadImageFileSystem(image_path);




        Color* data = image.data();
        cout << "You can now get pointer access to the linear start" << endl;
        cout << "image.data(): " << image.data() << endl << endl;

        Color* begin = image.begin();
        Color* end = image.end();
        cout << "Now we have access to begin() and end() methods." << endl;
        cout << "image.begin(): " << image.begin() << endl;
        cout << "image.end(): " << image.end() << endl;
        cout << "This unlocks range iteration in for loops" << endl;
        int i = 0;
        for (auto c : image) { i++; }
        cout << "completed: " << i << " range iteration loops" << endl << endl;


        int y = 5;
        int x = 42;
        Color* row_ptr = image.rowPtr(y);
        cout << "Now we support pointer and iterator access for a given row (y)" << endl;
        cout << "image.rowPtr(y): " << row_ptr << endl;
        RowIterator r = image.row(y);
        cout << "image.row(y).data(): " << r.data() << endl;
        cout << "image.row(y).begin(): " << r.begin() << endl;
        cout << "image.row(y).end(): " << r.end() << endl;
        cout << "image.row(y)[x]: " << r[x] << endl;
        cout << "This unlocks range iteratrion in for loops with row" << endl;
        i = 0;
        for (auto r2 : image.row(y)) { i++; }
        cout << "completed: " << i << " range iteration loops over row" << endl;
        cout << "This also unlocks fill using chain from iterator" << endl;
        Color test_color(0, 255, 255);
        image.row(y).fill(test_color);
        cout << "Post fill, accessing first k elements in row: " << endl;
        for (int k = 0; k < 3; k++) { cout << r[k] << ", "; }
        cout << endl << endl;


        cout << "Now supporting region row iteration" << endl;
        Rect rect{Point(200, 100), 50, 75};
        RegionRowIterator rr = image.regionRows(rect);
        cout << "This unlocks range iteration where rows are the sentinel" << endl;
        int filled_elements = 0;
        int filled_rows = 0;
        for (auto row : rr) { 
            row.fill(Color(69, 42, 21)); 
            filled_elements += row.size();
            filled_rows++;
        }
        cout << "filled: " << filled_elements << " elements using region row iterator" << endl;
        cout << "filled: " << filled_rows << " rows using region row iterator" << endl;
        cout << "printing 3x3 elements in tl corner: " << endl;
        RegionRowIterator debug = image.regionRows(rect);
        for (int k = 0; k < 3; k++) { 
            RowIterator row = debug.row();
            for (int l = 0; l < 3; l++) { 
                cout << row[l] << ", ";
            }
            cout << endl;
            ++debug;
        }
        // does the above logic call for a region iterator? 
        cout << "This also greatly simplifies reading the region" << endl;
        int sum = 0;
        for (auto row : rr) { 
            for (auto c : row) {
                sum += c.r + c.g + c.b;
            }
        }
        cout << "sum of region: " << sum << endl << endl;

        // TODO replace this with logger save
        // string save_path = save_dir + "iterator_test.jpg";
        // image::io::saveImageFileSystem(image, save_path);


        cout << "finally we support region iterators" << endl;
        cout << "printing a 3x5 grid as a flat sequence" << endl;
        Point tl(200, 100);
        int dx = 3;
        int dy = 5;
        int count = 0;
        for (auto px : image.region(Rect{tl, dx, dy})) { 
            cout << px << ", ";
            count++;
        }
        cout << endl << endl;
        cout << "count: " << count << endl;
        


    }
}