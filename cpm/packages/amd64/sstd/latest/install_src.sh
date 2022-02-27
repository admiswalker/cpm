#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install sstd/latest -------------------------------------------------'

mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

fName='sstd-latest.tar.gz'
fName_base='sstd-latest'

CACHE_BASE=$CACHE_DIR/src/$fName_base

# unpacking the archive file
if [ ! -e $BUILD_DIR/SubStandardLibrary-SSTD--master ]; then
    unzip -n $CACHE_BASE/$fName -d $BUILD_DIR # zip
    #tar -zxf $CACHE_DIR/$libName/$fName -C $BUILD_DIR # tar.xz
fi

# installation
if [ ! -e $INST_PATH/lib/libsstd.a ]; then
    cd $BUILD_DIR/SubStandardLibrary-SSTD--master/sstd;
    
    make -j
    
    mkdir -p $INST_PATH/lib
    mkdir -p $INST_PATH/include
    cp -r lib/* -t $INST_PATH/lib
    cp -r include/* -t $INST_PATH/include
fi

#    '--------------------------------------------------------------------------------'
echo '--------------------------------------------------- end: install sstd/latest ---'

