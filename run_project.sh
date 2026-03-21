#!/usr/bin/env bash

# This script is used to run cmake in the build directory.
# TODO make script env invariant
# TODO make versions of opencv + other libs dynamic install + check
# TODO add d flag to destroy Build folder and c for make clean
# TODO remove images from Results folder somehow

echo "Running cmake in the Build Directory"


### --- Parse Args --- ###

# Mac getopt cannot handle longoptions correctly TODO: make this system invariant
GETOPT=$(brew --prefix gnu-getopt)/bin/getopt

ARGS=$("$GETOPT" --options cr --longoptions clean_build,run -- "$@")
eval set -- "$ARGS"

bool_clean_build=false
bool_run_build=true

while true; do
    case "$1" in 
        -c | --clean_build ) bool_clean_build=true; shift ;;
        -r | --run ) bool_run_build=true; shift ;;
        -- ) break;;
    esac
done

### --- Build Project --- ###

if [ "$bool_clean_build" = true ] ; then
    echo "Removing build directory "
    rm -rf build
fi

mkdir -p build

cd build

cmake ../src

make

if [ "$bool_run_build" = true ] ; then  
    ./mosaic_tiler
fi