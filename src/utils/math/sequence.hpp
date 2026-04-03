#pragma once 

#include <vector>

using std::vector;

namespace math::sequence { 

    vector<int> uniformSamples(int min, int max, int num_elements);
    vector<int> uniformSamplesBounds(int min, int max, int num_elements);

}