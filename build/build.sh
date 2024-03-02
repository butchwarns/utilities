#! /bin/bash

# Allow this script to be run from different working directory without messing up relative paths
scriptdir="$(dirname "$0")"
cd "$scriptdir"

# Check the first argument for build type
build_type="debug"
if [ -z "$1" ]; then
    echo "No argument supplied. Please specify 'release' or 'debug'."
    echo "(Defaulting to $build_type build!)"

else
    build_type=$1
fi

# Run cmake with the determined build type
cmake .. -GUnix\ Makefiles -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type
cmake --build . --config $build_type
