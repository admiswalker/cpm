#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install cmake/3.20.1 ------------------------------------------------'

mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

fName='cmake-3.20.1.tar.gz'
fName_base=${fName%.*.*} # cmake-3.20.1
libName=${fName%-*}      # cmake

# unpacking the archive file
if [ ! -e $BUILD_DIR/$fName_base ]; then
    tar -zxf $CACHE_DIR/$fName -C $BUILD_DIR # tar.xz
fi

# installation
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/$fName_base;
    ./configure --prefix=$INST_PATH -- -DCMAKE_USE_OPENSSL=OFF
    
    make -j
    make install
fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------------- end: install cmake/3.20.1 ---'

