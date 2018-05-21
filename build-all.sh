#!/bin/bash

#
# Create 'build' directory
#
rm -rf build || exit 1
mkdir build || exit 1
cd build || exit 1

make --version  || exit 1
flex --version  || exit 1
bison --version || exit 1
perl --version  || exit 1


../configure \
--enable-debug \
--enable-coverage \
--enable-cassert \
--enable-depend \
CFLAGS='-O0' || exit 1

make -j5 || exit 1
make check || exit 1



