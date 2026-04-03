cmake_minimum_required(VERSION 3.10)
project(MosaicTiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(OpenCV REQUIRED)

# Collect all source files
add_executable(mosaic_tiler

    app/run_routines.cpp
    app/app.cpp
    
    data/image/image.cpp
    data/image/io.cpp

    routines/mosaic/mosaic.cpp
    routines/pop_art/pop_art.cpp
    routines/grid/grid.cpp

    utils/math/geometry.cpp
    utils/math/kernel.cpp
    utils/math/sequence.cpp
    utils/graphics/graphics.cpp
    utils/graphics/line.cpp
    utils/random/random.cpp
    utils/transform/resize.cpp
    utils/filter/color.cpp
    utils/filter/blur.cpp
    utils/filter/edge.cpp

    ../test/routines/mosaic/mosaic_test.cpp




    main.cpp
)

# Add includes
target_include_directories(mosaic_tiler PRIVATE

    app

    data/image

    routines/mosiac
    routines/pop_art
    routines/grid

    utils/math
    utils/graphics
    utils/random
    utils/transform
    utils/filter

    ../test
    ${OpenCV_INCLUDE_DIRS}

    
)

# Link OpenCV
target_link_libraries(mosaic_tiler ${OpenCV_LIBS})
