#!/bin/bash -e
set -x

cd "$(dirname "$0")"
ROOT=$(pwd)

gh release create "$GITHUB_REF_NAME" -F ./CHANGELOG.md ../binaries/*.zip