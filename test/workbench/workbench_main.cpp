#include "workbench_main.hpp"
#include "examples/iterator_examples.hpp"
#include "examples/grid_workbench.hpp"
#include "examples/pixelate_workbench.hpp"
#include "../../src/data/image/io.hpp"
#include "logger.hpp"

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <exception>

using std::cout, std::endl;
using std::string;
using logger::Logger, logger::UserEscapeSignal;

namespace workbench { 

    // Define all workbenches here
    // Some might be commented out for testing purposes
    void runAll(string image_path, Logger& logger) { 

        runIterator(image_path, logger);
        // runGrid(image_path, logger);
        runPixelate(image_path, logger);

    }

    // This function wrapper exists to catch user input
    // If the user hits escape or q, then the logger forces an early return
    void runWorkbench(string image_path, string save_dir) { 

        Logger my_logger("workbench_window", save_dir);
        my_logger.initCV();

        try { 
            runAll(image_path, my_logger);
        }
        catch (const UserEscapeSignal& s) { 
            cout << "User has exited the workbench" << endl;
        }
        catch (const std::exception& e) { 
            cerr << "Real exception: " << e.what() << endl;
        }
        
        cv::destroyAllWindows();
    }


}