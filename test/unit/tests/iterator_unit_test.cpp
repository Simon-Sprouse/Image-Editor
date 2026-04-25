#include "iterator_unit_test.hpp"
#include "../../src/data/shapes/shapes.hpp"

#include <iostream>
#include <vector>

using std::cout, std::cerr, std::endl;
using std::vector, std::to_string;
using namespace image;
using shapes::Rect;

namespace unit_test::iterator {



    void testRegionIterator(Image image) { 
        cout << "hello from region iterator unit test" << endl;
        cout << "image size: " << image.size() << endl;


        Point tl = Point(200, 100);
        int dx = 50;
        int dy = 75;
        Rect rect{tl, dx, dy};
        int region_size = dx * dy;


        // construction
        RegionIterator ri = image.region(rect); // better test lol

        // num iterations
        int num_iterations = 0;
        for (auto px : image.region(rect)) { 
            num_iterations++;
        }
        assertEqual(region_size, num_iterations, "num iterations in region");
        // todo enforce gt, ts ordering

        // correctness
        vector<Color> gt;
        gt.reserve(region_size);
        int pointer = image.getLinearIndex(tl);
        for (int y = 0; y < dy; y++) { 
            for (int x = 0; x < dx; x++) { 
                gt.push_back(image.at(pointer + x));
            }
            pointer += image.getWidth();
        }
        // TODO above is an old pattern
        // this absolutely screams for a RegionWithIndex iterator type
        // that way we could check subregion equality by running with iterator and then checking the indx of iterator

        vector<Color> ts;
        ts.reserve(region_size);
        for (auto px : image.region(rect)) { 
            ts.push_back(px);
        }

        assertEqualVector(gt, ts, "pixels in subregion match");

        cout << endl;
    }


    void testRowIterator(Image image) { 
        cout << "hello from row iterator unit test" << endl;
        cout << "image size: " << image.size() << endl;

        int y = 30;
        int width = image.getWidth();

        // construction
        RowIterator ri = image.row(y);

        // num iterations 
        int num_iterations = 0;
        for (auto px : image.row(y)) { 
            num_iterations++;
        }
        assertEqual(width, num_iterations, "num iterations for row");

        // correctness
        vector<Color> gt;
        gt.reserve(width);
        int row_start_index = image.getLinearIndex(0, y);
        for (int x = 0; x < width; x++) { 
            gt.push_back(image.at(row_start_index + x));
        }

        vector<Color> ts;
        ts.reserve(width);
        for (auto px : image.row(y)) { 
            ts.push_back(px);
        }

        assertEqualVector(gt, ts, "pixels in row match");

        cout << endl;

    }

    void testRegionRowIterator(Image image) { 
        cout << "hello from region row iterator unit test" << endl;
        cout << "image size: " << image.size() << endl;

        Point tl = Point(200, 100);
        int dx = 50;
        int dy = 75;
        Rect rect{tl, dx, dy};
        int region_size = dx * dy;
        

        // constructor
        RegionRowIterator rri = image.regionRows(rect);

        // num iterations
        int num_iterations_row = 0;
        int num_iterations_px = 0;
        for (auto row : image.regionRows(rect)) { 
            for (auto px : row) { 
                num_iterations_px++;
            }
            num_iterations_row++;
        }

        assertEqual(dy, num_iterations_row, "number of rows in iterator");
        assertEqual(region_size, num_iterations_px, "number of px in region");

        // correctness

        // test individual row
        int row_number = 3;

        vector<Color> gt;
        gt.reserve(dy);
        for (int x = 0; x < dx; x++) { 
            gt.push_back(image.at(tl.x + x, tl.y + row_number));
        }

        vector<Color> ts;
        gt.reserve(dy);
        RegionRowIterator rri_row_test = image.regionRows(rect);
        for (int i = 0; i < row_number; i++) { 
            ++rri_row_test; 
            // todo postfix and other completeness for iterators
        }
        for (auto px: rri_row_test.row()) { 
            ts.push_back(px); 
        }

        assertEqualVector(gt, ts, "pixels in row: " + to_string(row_number) + " match");


        // test region read
        vector<Color> gt_region;
        gt_region.reserve(region_size);
        int pointer = image.getLinearIndex(tl);
        for (int y = 0; y < dy; y++) { 
            for (int x = 0; x < dx; x++) { 
                gt_region.push_back(image.at(pointer + x));
            }
            pointer += image.getWidth();
        }

        vector<Color> ts_region;
        ts_region.reserve(region_size);
        for (auto row : image.regionRows(rect)) { 
            for (auto px : row) { 
                ts_region.push_back(px);
            }
        }
        
        assertEqualVector(gt_region, ts_region, "pixels in region match");
        cout << endl;


    }

    // TODO: 
    // test write operations using iterators
    // test const iterators




}