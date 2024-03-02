#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="utilities"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT"

# Make folder for built plugins
cd "$ROOT/ci_cd"
rm -Rf bin
mkdir bin

# Build in release mode
cd "$ROOT/build"
./build.sh release

# Copy plugin builds to dedicated folder
cp -R "$ROOT/build/${PLUGIN}_artefacts/Release/AU/$PLUGIN.component" "$ROOT/ci_cd/bin"
cp -R "$ROOT/build/${PLUGIN}_artefacts/Release/VST3/$PLUGIN.vst3" "$ROOT/ci_cd/bin"
