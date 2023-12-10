#!/bin/bash -e

# Disable shell debug output
set +x

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/"

echo  "##########################################"
echo -e "\nBuilding Installer..\n"
/usr/local/bin/packagesbuild --project ./packaging/mac/bw_utility.pkgproj
echo  "##########################################"