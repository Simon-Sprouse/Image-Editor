cmake_minimum_required(VERSION 3.10)
project(MosaicTiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(OpenCV REQUIRED)

# Collect all source files
add_executable(mosaic_tiler

    app/run_pipelines.cpp
    app/app.cpp
    
    data/image/image.cpp
    data/image/io.cpp

    pipelines/mosaic/mosaic.cpp
    pipelines/pop_art/pop_art.cpp
    pipelines/grid/grid.cpp
    pipelines/pixelate/pixelate.cpp

    functions/math/geometry.cpp
    functions/math/kernel.cpp
    functions/math/sequence.cpp
    functions/graphics/graphics.cpp
    functions/graphics/line.cpp
    functions/graphics/polygon.cpp
    functions/random/random.cpp
    functions/transform/resize.cpp
    functions/filter/color.cpp
    functions/filter/blur.cpp
    functions/filter/edge.cpp


    ../test/workbench/workbench_main.cpp
    ../test/workbench/logger.cpp
    ../test/workbench/examples/iterator_examples.cpp
    ../test/workbench/examples/grid_workbench.cpp
    ../test/workbench/examples/pixelate_workbench.cpp
    ../test/unit/unit_test_main.cpp
    ../test/unit/tests/iterator_unit_test.cpp
    



    main.cpp
)

# Add includes
target_include_directories(mosaic_tiler PRIVATE

    app

    data/image

    pipelines/mosiac
    pipelines/pop_art
    pipelines/grid

    functions/math
    functions/graphics
    functions/random
    functions/transform
    functions/filter

    ../test
    ${OpenCV_INCLUDE_DIRS}

    
)

# Link OpenCV
target_link_libraries(mosaic_tiler ${OpenCV_LIBS})
