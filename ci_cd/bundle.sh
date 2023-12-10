#!/bin/bash -e

# Disable shell debug output
set +x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/bin"
pwd

cp -r ../packaging/mac/build/$PLUGIN.pkg $PLUGIN.pkg

echo  "##########################################"
echo -e "\nCreate .zip archive\n"

zip -r ${PLUGIN}_mac.zip $PLUGIN.vst3 $PLUGIN.component $PLUGIN.pkg

echo  "##########################################"