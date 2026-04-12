#include "iterator_unit_test.hpp"

#include <iostream>
#include <vector>

using std::cout, std::cerr, std::endl;
using std::vector;
using namespace image;

namespace unit_test::iterator {



    void testRegionIterator(Image image) { 
        cout << "hello from iterator unit test" << endl;
        cout << "image size: " << image.size() << endl;


        int total_r = 0;
        for (int i = 0; i < image.getFlatSize(); i++) { 
            total_r += image.at(i).r;
        }
        cout << "total_r: " << total_r << endl;

        Point tl = Point(200, 100);
        int dx = 50;
        int dy = 75;
        int region_size = dx * dy;


        // construction
        RegionIterator ri = image.region(tl, dx, dy); // better test lol

        // num iterations
        int iter_sum = 0;
        for (auto px : image.region(tl, dx, dy)) { 
            iter_sum++;
        }
        assertEqual(iter_sum, region_size, "num iterations in region");

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
        for (auto px : image.region(tl, dx, dy)) { 
            ts.push_back(px);
        }

        assertEqualVector(gt, ts, "pixels in subregion match");


    }
}