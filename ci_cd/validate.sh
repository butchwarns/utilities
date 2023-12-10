#!/bin/bash -e

# Enable shell debug output
set -x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/"

# Run pluginval on the VST3
echo  "##########################################"
echo -e "\nValidating VST3 using pluginval..\n"
curl -LO "https://github.com/Tracktion/pluginval/releases/download/v1.0.3/pluginval_macOS.zip"
7z x pluginval_macOS.zip
./pluginval.app/Contents/MacOS/pluginval --strictness-level 10 --verbose --validate-in-process "${PLUGIN}.vst3" || exit 1
echo -e "\nAll tests passed!\n"
echo  "##########################################"