#! /bin/bash

# Allow this script to be run from different working directory without messing up relative paths
scriptdir="$(dirname "$0")"
cd "$scriptdir"

# Check the first argument for build type
if [ -z "$1" ]; then
    echo "No argument supplied. Please specify 'release' or 'debug'."
    echo "(Defaulting to release build!)"

    build_type="release"
else
    build_type=$1
fi

# Run cmake with the determined build type
cmake .. -GUnix\ Makefiles -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type
cmake --build . --config $build_type
