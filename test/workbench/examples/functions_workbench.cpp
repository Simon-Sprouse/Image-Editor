#include "functions_workbench.hpp"
#include "../../../src/functions/random/random.hpp"
#include "../../../src/data/shapes/shapes.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace logger;

namespace workbench { 
    void runRandom(string image_path, Logger logger) { 

        logger.start("test random");
        cout << "Hello from random workbench" << endl;
        logger.stop("test random");

        // todo scope tests? 
        // todo logger -> log rename 
        logger.start("lcg");
        {
            // todo - is this enough entropy? 
            uint32_t seed = 93u;

            // make a single random number
            uint32_t random_int = random_gen::lcg(seed);
            cout << "random int: " << random_int << endl;

            // fill vector with random numbers
            int num_random_iterations = 10;
            vector<int> random_vector;
            for (int i = 0; i < num_random_iterations; i++){ 
                random_vector.push_back(random_gen::lcg(seed + i));
            }        
            shapes::printVector<int>(random_vector, 5);
            cout << endl;
            logger.stop("lcg"); // separate save (and save for display) and stop
        }   
        

    }
}
