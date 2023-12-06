#! /bin/bash -e

# Disable shell debug output
set +x

# Allow this script to be run from different working directory without messing up relative paths
scriptdir="$(dirname "$0")"
cd "$scriptdir"

PLUGIN="bw_utility"

# Go to project root folder
ROOT=$(cd "$(dirname "$0")/.."; pwd)
cd "$ROOT"
echo "$ROOT"

# Get name of current git branch
BRANCH=${GITHUB_REF##*/}
echo "$BRANCH"

# Make folder for built plugins
cd "$ROOT/ci"
rm -Rf bin
mkdir bin

# Build in release mode
cd "$ROOT"
cmake --preset xcode
cmake --build --preset xcode --config Release

# Copy plugin builds to dedicated folder
cp -R "$ROOT/Builds/xcode/${PLUGIN}_artefacts/Release/AU/$PLUGIN.component" "$ROOT/ci/bin"
cp -R "$ROOT/Builds/xcode/${PLUGIN}_artefacts/Release/VST3/$PLUGIN.vst3" "$ROOT/ci/bin"

# Turn our base64-encoded certificate back to a regular .p12 file
echo $MACOS_CERTIFICATE | base64 --decode > certificate.p12

# We need to create a new keychain, otherwise using the certificate will prompt
# with a UI dialog asking for the certificate password, which we can't
# use in a headless CI environment
security create-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain 
security default-keychain -s build.keychain
security unlock-keychain -p "$MACOS_CI_KEYCHAIN_PWD" build.keychain
security import certificate.p12 -k build.keychain -P "$MACOS_CERTIFICATE_PWD" -T /usr/bin/codesign
security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k "$MACOS_CI_KEYCHAIN_PWD" build.keychain

# Codesign

# We finally codesign our app bundle, specifying the Hardened runtime option
cd "$ROOT/ci/bin"
/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_NAME" --options runtime $PLUGIN.vst3 -v
/usr/bin/codesign --force -s "$MACOS_CERTIFICATE_NAME" --options runtime $PLUGIN.component -v

# Notarize

cd "$ROOT/ci/bin"

# Store the notarization credentials so that we can prevent a UI password dialog
# from blocking the CI
echo "Create keychain profile"
xcrun notarytool store-credentials "notarytool-profile" --apple-id "$PROD_MACOS_NOTARIZATION_APPLE_ID" --team-id "$PROD_MACOS_NOTARIZATION_TEAM_ID" --password "$PROD_MACOS_NOTARIZATION_PWD"

# We can't notarize an app bundle directly, but we need to compress it as an archive.
# Therefore, we create a zip file containing our app bundle, so that we can send it to the
# notarization service
echo "Creating temp notarization archive"
zip -r ${PLUGIN}_Mac.zip $PLUGIN.vst3 $PLUGIN.component

# Here we send the notarization request to the Apple's Notarization service, waiting for the result.
# This typically takes a few seconds inside a CI environment, but it might take more depending on the App
# characteristics. Visit the Notarization docs for more information and strategies on how to optimize it if
# you're curious
echo "Notarize app"
xcrun notarytool submit --verbose "$PLUGIN.zip" --keychain-profile "notarytool-profile" --wait --timeout 30m

# Finally, we need to "attach the staple" to our executable, which will allow our app to be
# validated by macOS even when an internet connection is not available.
echo "Attach staple"
xcrun stapler staple $PLUGIN.vst3
xcrun stapler staple $PLUGIN.component

# Create zip archive
zip -r ${PLUGIN}_Mac.zip $PLUGIN.vst3 $PLUGIN.component