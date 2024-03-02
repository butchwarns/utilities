#!/bin/bash -e

# Disable shell debug output
set +x

PLUGIN="utilities"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/bin"

echo  "##########################################"
echo -e "\nUploading GitHub release.. $1\n"

gh release create "$1" -F ../../CHANGELOG.md ${PLUGIN}_mac.zip

echo  "##########################################"