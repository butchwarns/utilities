#!/bin/bash -e

# Disable shell debug output
set +x

SCRIPT_DIR="$(dirname "$0")"
cd "$SCRIPT_DIR"

echo  "##########################################"
echo -e "\nBuilding Installer..\n"

packagesbuild --reference-folder ./packaging/mac --project ./packaging/mac/utilities.pkgproj

echo  "##########################################"