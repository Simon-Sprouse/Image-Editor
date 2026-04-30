#pragma once 

#include <vector>

using std::vector;

namespace math::sequence { 

   
    vector<int> uniformSamples(int min, int max, int num_elements); // todo: burn this with fire
    vector<int> uniformSamplesBounds(int min, int max, int num_elements);
    vector<int> ratioSamples(int min, int max, double ratio);
    vector<int> randomSamples(int min, int max, int num_elements, uint32_t seed);


}