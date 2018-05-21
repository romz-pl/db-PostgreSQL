#!/bin/bash

#
# Create 'build' directory
#
rm -rf build || exit 1
mkdir build || exit 1
cd build || exit 1

../configure || exit 1
make -j5 || exit 1
make check || exit 1



