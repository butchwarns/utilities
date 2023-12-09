#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="bw_utility"

# Go to project root folder
ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT"

# Make folder for built plugins
cd "$ROOT/ci_cd"
rm -Rf bin
mkdir bin

# Build in release mode
cd "$ROOT/build"
./build_release.sh

# Copy plugin builds to dedicated folder
cp -R "$ROOT/build/${PLUGIN}_artefacts/Release/AU/$PLUGIN.component" "$ROOT/ci_cd/bin"
cp -R "$ROOT/build/${PLUGIN}_artefacts/Release/VST3/$PLUGIN.vst3" "$ROOT/ci_cd/bin"

build/build_debug.sh# Run pluginval on the VST3
echo  "##########################################"
echo -e "\nValidating VST3 using pluginval..\n"
cd "$ROOT/ci_cd/bin"
curl -LO "https://github.com/Tracktion/pluginval/releases/download/v1.0.3/pluginval_macOS.zip"
7z x pluginval_macOS.zip
./pluginval.app/Contents/MacOS/pluginval --strictness-level 10 --verbose --validate-in-process "${PLUGIN}.vst3" || exit 1
echo -e "\nAll tests passed!\n"
echo  "##########################################"