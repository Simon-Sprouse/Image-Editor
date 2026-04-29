#include "functions_workbench.hpp"
#include "../../../src/functions/random/random.hpp"
#include "../../../src/data/shapes/shapes.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace logger;

namespace workbench { 
    void runRandom(string image_path, Logger logger) { 

        logger.start("test random");
        cout << "Hello from random workbench" << endl;
        logger.stop("test random");

        // todo - is this enough entropy? 
        using clock = std::chrono::system_clock;
        uint32_t seed = static_cast<uint32_t>(
            clock::to_time_t(clock::now())
        );
        cout << "seed: " << seed << endl;
        // uint32_t seed = 420u;

        // todo scope tests? 
        // todo logger -> log rename 
        logger.start("lcg");
        {
            cout << "lcg hash function: " << endl;
            // todo what is difference between hash/bit_mixer/prng?

            // fill vector with random numbers
            int num_random_iterations = 10;
            vector<uint32_t> random_vector;
            for (int i = 0; i < num_random_iterations; i++){ 
                random_vector.push_back(random_gen::lcg(seed + i));
            }        
            shapes::printVector<uint32_t>(random_vector, 5);

            logger.stop("lcg"); // separate save (and save for display) and stop
        }   

        logger.start("triple32");
        { 
            cout << "triple32 hash function" << endl;

            // fill vector with random numbers
            int num_random_iterations = 10;
            vector<uint32_t> random_vector;
            for (int i = 0; i < num_random_iterations; i++){ 
                random_vector.push_back(random_gen::triple32(seed + i));
            }        
            shapes::printVector<uint32_t>(random_vector, 5);


            logger.stop("triple32");
        }


        logger.start("lemire's algorithm");
        {

            // create vector of randoms
            vector<uint32_t> randoms;
            for (int i = 0; i < 10; i++) { 
                int random_number = random_gen::triple32(seed + i);
                randoms.push_back(random_number);
            }
            cout << "randoms:" << endl;
            shapes::printVectorNewline<uint32_t>(randoms);
            cout << endl;


            // test various ranges
            for (int i = 0; i < 15; i++) { 
                int range = std::pow(2, i);
                
                // for this given range, generate apply bounds
                vector<uint32_t> bounded_randoms;
                for (auto random_number : randoms) { 
                    uint32_t bounded = random_gen::random_bounded(random_number, range);
                    bounded_randoms.push_back(bounded);
                }
                
                cout << "range: " << 0 << " to " << range << endl;
                shapes::printVector<uint32_t>(bounded_randoms);
                cout << endl;
            }
            
            
            logger.stop("lemire's algorithm");
        }


        logger.start("lemire's algorithm x multi");
        {
            vector<uint32_t> randoms;
            for (int i = 0; i < std::pow(10, 6); i++) { 
                int random_number = random_gen::triple32(seed + i);
                int bouned = random_gen::random_bounded(random_number, 512);
            }
            logger.stop("lemire's algorithm x multi");
        }

    }
}
