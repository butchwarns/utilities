#!/bin/bash -e

# Enable shell debug output
set -x

PLUGIN="bw_utility"

# Go to project root folder
ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/bin"

gh release create "$1" -F ../../CHANGELOG.md ${PLUGIN}_*.zip