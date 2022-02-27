#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install googletest/1.11.0 -------------------------------------------'

mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

fName='googletest-1.11.0.tar.gz'
fName_base='googletest-1.11.0'

# unpacking the archive file
if [ ! -e $BUILD_DIR/googletest-release-1.11.0 ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CACHE_DIR/$fName -C $BUILD_DIR # tar.xz
fi

# installation
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/googletest-release-1.11.0;
    mkdir -p build; cd build; cmake ..; make
    
    mkdir -p $INST_PATH/lib
    mkdir -p $INST_PATH/include
    
    cp -r lib/* -t $INST_PATH/lib
    cd ../googletest; cp -r include/* -t $INST_PATH/include
fi

#    '--------------------------------------------------------------------------------'
echo '--------------------------------------------- end: install googletest/1.11.0 ---'

