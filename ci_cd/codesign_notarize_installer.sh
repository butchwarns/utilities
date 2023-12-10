#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac/build"

# Codesign & Notarize

echo  "##########################################"
echo -e "\nCodesign Installer\n"
/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_NAME" --options runtime $PLUGIN.pkg -v
echo  "##########################################"

zip -r ${PLUGIN}_installer_mac.zip $PLUGIN.pkg

echo  "##########################################"
echo -e "\nNotarize\n"
xcrun notarytool submit --verbose "${PLUGIN}_installer_mac.zip" --keychain-profile "notarytool-profile" --wait --timeout 30m
echo  "##########################################"

echo "Attach staple"
xcrun stapler staple $PLUGIN.pkg