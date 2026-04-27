#pragma once

#include "../../functions/math/sequence.hpp"

#include <vector>

using std::vector;


namespace variant_fn { 

     enum class SequenceMode { 
        uniform,
        ratio
    };

    // common params accross all variants
    struct SequenceCommon { 

        // common
        SequenceMode mode; // will decide function dispatch
        int min;
        int max;

        // uniform
        int num_elements;

        // ratio
        double ratio;
    };

    inline vector<int> sequenceFn(const SequenceCommon& p) { 
        switch (p.mode) { 
            case (SequenceMode::uniform): return math::sequence::uniformSamplesBounds(p.min, p.max, p.num_elements);
            case (SequenceMode::ratio): return math::sequence::ratioSamples(p.min, p.max, p.ratio);
        }
    }

}