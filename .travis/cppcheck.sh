#!/usr/bin/env bash

if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
  set -x
  cppcheck src/ --enable=warning,style,performance,portability --inconclusive --error-exitcode=1
  cppcheck lib/Physics/src --enable=warning,style,performance,portability --inconclusive --error-exitcode=1
fi
