#include "sequence.hpp"

#include <iostream>
#include <cassert>
#include <cmath>



using namespace std;



// preconditional checking internal
namespace {

    enum class InputStatus { OK, EMPTY };

    InputStatus validateUniformSamples(int min, int max, int num_elements) { 

        int range = max - min;

        assert(max >= 0);
        assert(min >= 0);
        assert(num_elements >= 0);
        assert(range >= num_elements);

        if (num_elements == 0 || min == max) { 
            return InputStatus::EMPTY;
        }
        return InputStatus::OK;
    }


    InputStatus validateUniformSamplesBounds(int min, int max, int num_elements) { 


        int range = max - min;

        assert(max >= 0);
        assert(min >= 0);
        assert(num_elements >= 0);
        assert(range >= num_elements);

        if (num_elements <= 1 || min == max) { 
            return InputStatus::EMPTY;
        }
        return InputStatus::OK;

    }


}


namespace math::sequence { 



    // evenly spaced intervals 
    vector<int> uniformSamples(int min, int max, int num_elements) { 

        if (validateUniformSamples(min, max, num_elements) ==  InputStatus::EMPTY) { return {}; }


        vector<int> output;
        output.reserve(num_elements);

        int range = max - min;
        double interval_size = static_cast<double>(range) / (num_elements + 1);

        for (int i = 1; i < num_elements + 1; i++) { 
            output.push_back(static_cast<int>(std::round(min + i * interval_size)));
        }


        return output;

    }



    // evenly spaced intervals with indicies at bounds
    vector<int> uniformSamplesBounds(int min, int max, int num_elements) { 

        if (validateUniformSamplesBounds(min, max, num_elements) ==  InputStatus::EMPTY) { return {}; }


        vector<int> output = uniformSamples(min, max, num_elements - 2);
        output.insert(output.begin(), min);
        output.push_back(max);
        
        return output;

    }



    vector<int> ratioSamples(int min, int max, double ratio) { 

        vector<int> output;
        output.push_back(min); // todo: better way to add bounds

        int l_pointer = min;
        int range = max - l_pointer;

        // const double inv_phi = 0.6180339887498948; // todo: better way to do this

        while (range > 1) { 
            int step = std::max(1, static_cast<int>(range * ratio));
            int new_index = l_pointer + step;
            output.push_back(new_index);
            l_pointer = new_index;
            range = max - l_pointer;
        }

        output.push_back(max);
        return output;
    }









}






