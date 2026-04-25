#pragma once 

#include <vector>

using std::vector;

namespace math::sequence { 

    enum class SequenceType { 
        uniform,
        ratio
    };

    struct SequenceParams { 

        // common
        SequenceType type;
        int min;
        int max;

        // uniform
        int num_elements;

        // ratio
        double ratio;
    };

    vector<int> sequenceSelector(const SequenceParams& p);

    vector<int> uniformSamples(int min, int max, int num_elements); // todo: burn this with fire
    vector<int> uniformSamplesBounds(int min, int max, int num_elements);
    vector<int> ratioSamples(int min, int max, double ratio);


}