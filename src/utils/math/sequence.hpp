#pragma once 

#include <vector>

using std::vector;

namespace math::sequence { 

    enum class SequenceType { 
        uniform,
        golden_ratio
    };

    struct SequenceParams { 

        // common
        int min;
        int max;

        // uniform
        int num_elements;
    };

    vector<int> sequenceSelector(const SequenceParams& p, SequenceType type);

    vector<int> uniformSamples(int min, int max, int num_elements); // todo: burn this with fire
    vector<int> uniformSamplesBounds(int min, int max, int num_elements);
    vector<int> goldenRatioSamples(int min, int max);


}