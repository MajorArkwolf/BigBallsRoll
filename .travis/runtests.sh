#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
  build/BigBalls --test
fi

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
  build/BigBalls.exe --test
fi