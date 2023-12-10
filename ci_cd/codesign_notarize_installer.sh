#! /bin/bash -e

# Enable shell debug output
set -x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac"

# Turn our base64-encoded certificate back to a regular .p12 file
echo $MACOS_CERTIFICATE_INSTALLER | base64 --decode > certificate_installer.p12

security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate_installer.p12 -k build.keychain -P "$MACOS_CERTIFICATE_INSTALLER_PWD" -T /usr/bin/codesign

echo  "##########################################"
echo -e "\nCodesign Installer\n"

/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_INSTALLER_NAME" --options runtime ./build/$PLUGIN.pkg -v --timestamp

echo  "##########################################"
echo -e "\nNotarize Installer\n"

echo "Creating temporary notarization archive"
zip -r ${PLUGIN}_installer_mac.zip ./build/$PLUGIN.pkg
xcrun notarytool submit --verbose "${PLUGIN}_installer_mac.zip" --keychain-profile "notarytool-profile" --wait --timeout 30m

echo  "##########################################"
echo -e "\nStaple Installer\n"

echo "Attach staple"
xcrun stapler staple ./build/$PLUGIN.pkg

echo  "##########################################"
