#!/bin/bash -e

# Disable shell debug output
set +x

# Clean ci_cd folder

scriptdir="$(dirname "$0")"
cd "$scriptdir"

for item in *; do
    # Check if the item is a .sh file or the packaging folder
    if [[ ! $item == *.sh && ! $item == "packaging" ]]; then
        # If not, remove the item
        rm -rf "$item"
    fi
done

# Clean build folder

cd ../build

for item in *; do
    # Check if the item is a .sh file 
    if [[ ! $item == *.sh ]]; then
        # If not, remove the item
        rm -rf "$item"
    fi
done