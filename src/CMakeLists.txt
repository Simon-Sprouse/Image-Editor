cmake_minimum_required(VERSION 3.10)
project(MosaicTiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(OpenCV REQUIRED)

# Collect all source files
add_executable(mosaic_tiler

    app/run_mosaic.cpp
    
    data/image/image.cpp
    data/image/io.cpp

    routines/mosaic/mosaic.cpp

    utils/geometry/geometry.cpp
    utils/graphics/graphics.cpp
    utils/image_process/ImageProcess.cpp
    utils/random/random.cpp
    utils/transform/resize.cpp

    ../test/routines/mosaic/mosaic_test.cpp
    ../test/utils/geometry/geometry_test.cpp
    ../test/utils/graphics/graphics_test.cpp
    ../test/utils/image_process/image_process_test.cpp


    main.cpp
)

# Add includes
target_include_directories(mosaic_tiler PRIVATE

    app

    data/image

    routines/mosiac

    utils/geometry
    utils/graphics
    utils/image_process
    utils/random
    utils/transform

    ../test
    ${OpenCV_INCLUDE_DIRS}

    
)

# Link OpenCV
target_link_libraries(mosaic_tiler ${OpenCV_LIBS})
