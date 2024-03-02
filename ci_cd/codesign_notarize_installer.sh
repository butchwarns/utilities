#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="utilities"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac"


# Turn our base64-encoded certificate back to a regular .p12 file
echo $MACOS_CERTIFICATE_INSTALLER | base64 --decode > certificate_installer.p12

security default-keychain -s build.keychain
security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate_installer.p12 -k build.keychain -P "$MACOS_CERTIFICATE_INSTALLER_PWD" -T /usr/bin/productsign
security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k "$MACOS_CI_KEYCHAIN_PWD" build.keychain

echo  "##########################################"
echo -e "\nCodesign Installer\n"

cd "$ROOT/ci_cd/packaging/mac"
/usr/bin/productsign -s "$MACOS_CERTIFICATE_INSTALLER_NAME" --timestamp ./build/$PLUGIN.pkg ../../bin/$PLUGIN.pkg
rm -rf ./build/$PLUGIN.pkg

echo  "##########################################"
echo -e "\nNotarize Installer\n"

xcrun notarytool submit --verbose "../../bin/$PLUGIN.pkg" --keychain-profile "notarytool-profile" --wait --timeout 30m

echo  "##########################################"
echo -e "\nStaple Installer\n"

echo "Attach staple"
xcrun stapler staple ../../bin/$PLUGIN.pkg

echo  "##########################################"
