#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--- begin: install googletest/1.11.0 -------------------------------------------'
echo '--------------------------------------------------------------------------------'

mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

fName='googletest-1.11.0.tar.gz'
fName_base='googletest-1.11.0'

CACHE_BASE=$CACHE_DIR/src/$fName_base

# unpacking the archive file
if [ ! -e $BUILD_DIR/googletest-release-1.11.0 ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CACHE_BASE/$fName -C $BUILD_DIR # tar.xz
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/googletest-release-1.11.0;
    mkdir -p build; cd build; cmake ..; make
    
    cp -r lib/* -t $INST_PATH/lib
    cd ../googletest; cp -r include/* -t $INST_PATH/include
fi
# ----------------------------------------------- installation: end ---

#    '--------------------------------------------------------------------------------'
echo '--------------------------------------------- end: install googletest/1.11.0 ---'

