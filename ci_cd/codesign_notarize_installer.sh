#! /bin/bash -e

# Disable shell debug output
set +x

PLUGIN="bw_utility"

ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT/ci_cd/packaging/mac"

# Turn our base64-encoded certificate back to a regular .p12 file
echo $MACOS_CERTIFICATE_INSTALLER | base64 --decode > certificate_installer.p12

# We need to create a new keychain, otherwise using the certificate will prompt
# with a UI dialog asking for the certificate password, which we can't
# use in a headless CI environment
security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate_installer.p12 -k build.keychain -P "$MACOS_CERTIFICATE_INSTALLER_PWD" -T /usr/bin/codesign

# Codesign & Notarize

echo  "##########################################"
echo -e "\nCodesign Installer\n"

/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_INSTALLER_NAME" --options runtime $PLUGIN.pkg -v

echo  "##########################################"

# Store the notarization credentials so that we can prevent a UI password dialog
# from blocking the CI
echo "Create keychain profile"
xcrun notarytool store-credentials "notarytool-profile" --apple-id "$PROD_MACOS_NOTARIZATION_APPLE_ID" --team-id "$PROD_MACOS_NOTARIZATION_TEAM_ID" --password "$PROD_MACOS_NOTARIZATION_PWD"

echo  "##########################################"
echo -e "\nNotarize Installer\n"

echo "Creating temporary notarization archive"
zip -r ${PLUGIN}_plugins_mac.zip $PLUGIN.pkg
xcrun notarytool submit --verbose "${PLUGIN}_plugins_mac.zip" --keychain-profile "notarytool-profile" --wait --timeout 30m

echo  "##########################################"
echo -e "\nStaple Plug-Ins\n"

echo "Attach staple"
xcrun stapler staple $PLUGIN.vst3
xcrun stapler staple $PLUGIN.component