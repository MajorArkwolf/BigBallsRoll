#!/usr/bin/env bash

set -x

build_args='-G Ninja'

if [[ "${TRAVIS_EVENT_TYPE}" == "pull_request" ]]; then
    build_args+=' -D WarningsAsErrors:BOOL=ON '
fi

mkdir build && cd build
/usr/local/bin/cmake ${build_args} ..
ninja