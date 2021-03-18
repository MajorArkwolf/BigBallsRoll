#!/usr/bin/env bash

set -x

build_args='-DCMAKE_EXPORT_COMPILE_COMMANDS=ON .'

if [[ "${TRAVIS_EVENT_TYPE}" == "pull_request" ]]; then
    build_args+=' -DWarningsAsErrors:BOOL=ON '
fi

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
    mkdir -p build
    cd build
    cmake -S "../" -G "Visual Studio 15 2017" -DCMAKE_DISABLE_FIND_PACKAGE_WindowsSDK=ON "${build_args}" -D CMAKE_GENERATOR_PLATFORM=x64
    cmake --build .
else
  mkdir build && cd build
  /usr/local/bin/cmake -G Ninja "${build_args}" ..
  ninja
fi