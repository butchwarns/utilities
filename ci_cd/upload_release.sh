#!/bin/bash -e

# Enable shell debug output
set -x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/bin"

echo  "##########################################"
echo -e "\nUploading GitHub release $1\n"
gh release create "$1" -F ../../CHANGELOG.md ${PLUGIN}_*.zip
echo  "##########################################"