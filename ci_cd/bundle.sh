#!/bin/bash -e

# Disable shell debug output
set +x

PLUGIN="utilities"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/bin"
pwd

echo  "##########################################"
echo -e "\nCreate .zip archive\n"

# Bundle plugin installer, raw plugins and changelog
zip -r ${PLUGIN}_mac.zip $PLUGIN.vst3 $PLUGIN.component $PLUGIN.pkg ../CHANGELOG.md

echo  "##########################################"