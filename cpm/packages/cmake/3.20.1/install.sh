#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`

mkdir -p $CACHE_DIR
mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

URL=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1.tar.gz
fName=${URL##*/}         # cmake-3.20.1.tar.gz
fName_base=${fName%.*.*} # cmake-3.20.1
fName_ext=${fName#*.*.}  # tar.gz
libName=${fName%-*}      # cmake

URL_hash=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-SHA-256.txt
fName_hash=${URL_hash##*/} # cmake-3.20.1-SHA-256.txt

# installing depending packages
# - OpenSSL

# downloading source file
if [ ! -e $CACHE_DIR/$libName/$fName ]; then
    wget -P $CACHE_DIR/$libName $URL
fi
if [ ! -e $CACHE_DIR/$libName/$fName_hash ]; then
    wget -P $CACHE_DIR/$libName $URL_hash
fi

# check hash
cd $CACHE_DIR/$libName;
sha256sum -c --ignore-missing $CACHE_DIR/$libName/$fName_hash >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi
cd $CALL_DIR;

# unpacking the archive file
if [ ! -e $BUILD_DIR/$fName_base ]; then
    tar -zxf $CACHE_DIR/$libName/$fName -C $BUILD_DIR # tar.xz
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/$fName_base;
    ./configure --prefix=$$INST_PATH
    
    make -j
    make install
fi
# ----------------------------------------------- installation: end ---

