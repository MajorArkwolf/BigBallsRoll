#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" != "windows" ]]; then
  set -x
  tmp=$(mktemp -d)
  cd tmp
  wget https://cmake.org/files/v3.17/cmake-3.17.0-rc1-Linux-x86_64.tar.gz
  tar -xf cmake-3.17.0-rc1-Linux-x86_64.tar.gz
  cd cmake-3.17.0-rc1-Linux-x86_64
  sudo cp -rf {bin,share} /usr/local/
fi

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
  choco install -y windows-sdk-10.1 --version 10.1.18362.1
fi