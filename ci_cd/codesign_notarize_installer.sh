#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac/build"

echo $MACOS_CERTIFICATE | base64 --decode > certificate.p12

security create-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain 
security default-keychain -s build.keychain
security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate.p12 -k build.keychain -P "$MACOS_CERTIFICATE_PWD" -T /usr/bin/codesign
security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k "$MACOS_CI_KEYCHAIN_PWD" build.keychain

# Codesign & Notarize

echo  "##########################################"
echo -e "\nCodesign Plug-Ins\n"

/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_NAME" --options runtime $PLUGIN.pkg -v

echo  "##########################################"

echo "Create keychain profile"
xcrun notarytool store-credentials "notarytool-profile" --apple-id "$PROD_MACOS_NOTARIZATION_APPLE_ID" --team-id "$PROD_MACOS_NOTARIZATION_TEAM_ID" --password "$PROD_MACOS_NOTARIZATION_PWD"

echo  "##########################################"
echo -e "\nNotarize Installer\n"

echo "Creating temporary notarization archive"
zip -r ${PLUGIN}_installer_mac.zip $PLUGIN.pkg
xcrun notarytool submit --verbose "${PLUGIN}_installer_mac.zip" --keychain-profile "notarytool-profile" --wait --timeout 30m

echo  "##########################################"
echo -e "\nStaple Installer\n"

echo "Attach staple"
xcrun stapler staple $PLUGIN.pkg