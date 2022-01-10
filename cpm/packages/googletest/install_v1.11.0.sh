#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

mkdir -p $CACHE_DIR
mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

URL=https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
fName=${URL##*/}       # release-1.11.0.zip
fName_base=${fName%.*} # release-1.11.0
fName_ext=${fName#*.}  # zip
#libName=${fName%-*}   # release
libName=googletest     # googletest


# installing depending packages
# - gcc-8.4.0 as a base compiler
# - cmake

# downloading source file
if [ ! -e $CACHE_DIR/$libName/$fName ]; then
    wget -P $CACHE_DIR/$libName $URL
fi

# unpacking the archive file
if [ ! -e $BUILD_DIR/googletest-release-1.11.0 ]; then
    unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/googletest-release-1.11.0;
    mkdir -p build; cd build; cmake ..; make
    
    mv lib/ $INST_PATH
    cd ../googletest; mv include/ $INST_PATH
fi
# ----------------------------------------------- installation: end ---

