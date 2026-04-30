#pragma once

#include "../../functions/math/sequence.hpp"
#include "../../functions/random/random.hpp"

#include <vector>

using std::vector;


namespace variant_fn { 

     enum class SequenceMode { 
        uniform,
        ratio,
        random
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

        // random 
        uint32_t seed = random_gen::seedFromClock();
    };

    inline vector<int> sequenceFn(const SequenceCommon& p) { 
        switch (p.mode) { 
            case (SequenceMode::uniform): return math::sequence::uniformSamplesBounds(p.min, p.max, p.num_elements);
            case (SequenceMode::ratio): return math::sequence::ratioSamples(p.min, p.max, p.ratio);
            case (SequenceMode::random): return math::sequence::randomSamples(p.min, p.max, p.num_elements, p.seed);
        }
    }

}