#!/bin/sh

function build_project {
    xcrun xcodebuild -project "${1}" \
    -target "${2}" \
    -configuration "${3}" \
    -sdk "${4}" \
    ONLY_ACTIVE_ARCH=NO \
    BUILD_DIR="${5}" \
    ${6}
}

function make_fat_library {
    xcrun lipo -create "${1}" "${2}" -output "${3}"
}

