#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.
BUILD_DIR=$CALL_DIR/$BUILD_DIR; mkdir -p $BUILD_DIR # When using Docker, the absolute path is determined at run time.
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.


echo '--- begin: install sstd/1.0.0 --------------------------------------------------'
echo '--------------------------------------------------------------------------------'

URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/tags/v1.0.0.zip
fName=${URL##*/}       # v1.0.0.zip
fName_base=${fName%.*} # v1.0.0
fName_ext=${fName#*.}  # zip
#libName=${fName%-*}   # release
libName=sstd-1.0.0     # sstd

URL_hash=''
fName_hash=${URL_hash##*/} # openssl-1.1.1m.tar.gz.sha256

# installing depending packages
# - gcc-8.4.0 as a base compiler
# - cmake

# downloading source file
if [ ! -e $CACHE_DIR/$libName/$fName ]; then
    wget -P $CACHE_DIR/$libName $URL
fi

# check hash
#find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName) >/dev/null 2>&1
echo $(sha256sum $CACHE_DIR/$libName/$fName) | grep 'fd443523f98dadfb60d0bb85d3b4bd26aec68703655944fb96ab4a33b9de5084' >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

# unpacking the archive file
if [ ! -e $BUILD_DIR/SubStandardLibrary-SSTD--1.0.0 ]; then
    unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR # zip
    #tar -zxf $CACHE_DIR/$libName/$fName -C $BUILD_DIR # tar.xz
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/lib/libsstd.a ]; then
    cd $BUILD_DIR/SubStandardLibrary-SSTD--1.0.0/sstd;
    
    make -j
    
    cp -r lib/* -t $INST_PATH/lib
    cp -r include/* -t $INST_PATH/include
fi
# ----------------------------------------------- installation: end ---

echo '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: install sstd/1.0.0 ---'

