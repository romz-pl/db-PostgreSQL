#!/bin/bash

#
# Create 'build' directory
#
rm -rf build || exit 1
mkdir build || exit 1
cd build || exit 1

make --version

../configure \
--enable-debug \
--enable-coverage \
--enable-cassert \
--enable-depend || exit 1

make || exit 1
make check || exit 1



