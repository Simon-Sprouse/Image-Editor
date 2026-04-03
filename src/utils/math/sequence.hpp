#pragma once 

#include <vector>

using std::vector;

namespace math::sequence { 

    vector<int> evenSteps(int min, int max, int num_elements);
    vector<int> evenStepsWithBounds(int min, int max, int num_elements);

}