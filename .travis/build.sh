#!/usr/bin/env bash

set -x

build_args='-G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .'

if [[ "${TRAVIS_EVENT_TYPE}" == "pull_request" ]]; then
    build_args+=' -DWarningsAsErrors:BOOL=ON '
fi

mkdir build && cd build
/usr/local/bin/cmake ${build_args} ..
ninja