#include "variants_workbench.hpp"
#include "../../../src/variants/math/sequence_variants.hpp"
#include "../../../src/data/shapes/shapes.hpp"

using namespace logger;
using namespace std;

namespace workbench { 
    void sequenceVariant(string image_path, Logger logger) { 



        // // common
        // int min = 0;
        // int max = 100000;
        

        // logger.start("ratio");
        // double ratio = math::constants::inv_phi;
        // vector<int> r = math::sequence::ratioSamples(min, max, ratio);
        // shapes::printVector<int>(r);
        // cout << endl;
        // logger.stop("ratio");


        // logger.start("even");
        // int num_idx = 12;
        // vector<int> even = math::sequence::uniformSamplesBounds(min, max, num_idx); 
        // shapes::printVector<int>(r);
        // cout << endl;
        // logger.stop("even");

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