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

# Build in debug mode
cd "$ROOT/build"
./build.sh debug

# Copy plugin builds to dedicated folder
cp -R "$ROOT/build/${PLUGIN}_artefacts/Debug/AU/$PLUGIN.component" "$ROOT/ci_cd/bin"
cp -R "$ROOT/build/${PLUGIN}_artefacts/Debug/VST3/$PLUGIN.vst3" "$ROOT/ci_cd/bin"