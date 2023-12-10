#! /bin/bash -e

# Enable shell debug output
set -x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac"

# Turn our base64-encoded certificate back to a regular .p12 file
echo $MACOS_CERTIFICATE_INSTALLER | base64 --decode > certificate_installer.p12

security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate_installer.p12 -k build.keychain -P "$MACOS_CERTIFICATE_INSTALLER_PWD" -T /usr/bin/productsign

echo  "##########################################"
echo -e "\nCodesign Installer\n"

cd "$ROOT/ci_cd/packaging/mac"
/usr/bin/productsign --force -s "$MACOS_CERTIFICATE_INSTALLER_NAME" --timestamp ./build/$PLUGIN.pkg ../../bin/$PLUGIN.pkg

echo  "##########################################"
echo -e "\nNotarize Installer\n"

xcrun notarytool submit --verbose "../../bin/${PLUGIN}.pkg" --keychain-profile "notarytool-profile" --wait --timeout 30m

echo  "##########################################"
echo -e "\nStaple Installer\n"

echo "Attach staple"
xcrun stapler staple ../../bin/$PLUGIN.pkg

echo  "##########################################"
