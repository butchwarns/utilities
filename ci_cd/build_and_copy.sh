#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="utilities"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT"

# Check the first argument for build type
if [ "$1" == "debug" ]; then
    BUILD_TYPE="Debug"
elif [ "$1" == "release" ]; then
    BUILD_TYPE="Release"
else
    echo "Invalid argument. Please specify 'debug' or 'release'."
    exit 1
fi

# Make folder for built plugins
cd "$ROOT/ci_cd"
rm -Rf bin
mkdir bin

# Build plugin
cd "$ROOT/build"
./build.sh $1

# Copy plugin builds to dedicated folder
cp -R "$ROOT/build/${PLUGIN}_artefacts/$BUILD_TYPE/AU/$PLUGIN.component" "$ROOT/ci_cd/bin"
cp -R "$ROOT/build/${PLUGIN}_artefacts/$BUILD_TYPE/VST3/$PLUGIN.vst3" "$ROOT/ci_cd/bin"