#include "variants_workbench.hpp"
#include "../../../src/variants/math/sequence_variants.hpp"
#include "../../../src/data/shapes/shapes.hpp"

using namespace logger;
using namespace std;

namespace workbench { 
    void sequenceVariant(string image_path, Logger logger) { 

        // common params
        // todo variant_fn namespace is bad
        variant_fn::SequenceCommon common;
        common.min = 10;
        common.max = 1000;

        logger.start("sequence: random");
        {
            common.mode = variant_fn::SequenceMode::random;
            common.num_elements = 10;

            vector<int> seq = variant_fn::sequenceFn(common);
            
            shapes::printVector(seq, 5);
            logger.stop("sequence: random");
        }

    } 
}