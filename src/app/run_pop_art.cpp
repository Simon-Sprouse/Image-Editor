#include <string>


#include "run_pop_art.hpp"
#include "../routines/pop_art/pop_art.hpp"

using pop_art::PopArt, pop_art::Parameters;
using std::string;

namespace app {

    ImageResult runPopArt(const Image& image) { 

        Parameters params;
        params.num_splits = 3;

        PopArt my_pop_art(params);
        my_pop_art.loadExistingImage(image);
        my_pop_art.run();

        ImageResult output;
        output.label = "pop_art";
        output.image = my_pop_art.getCanvas();

        return output;

    }
}