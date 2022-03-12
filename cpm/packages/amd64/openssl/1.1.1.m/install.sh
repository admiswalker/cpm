#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.
BUILD_DIR=$CALL_DIR/$BUILD_DIR; mkdir -p $BUILD_DIR # When using Docker, the absolute path is determined at run time.
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.


echo '--- begin: install openssl/1.1.1m ----------------------------------------------'
echo '--------------------------------------------------------------------------------'

URL=https://www.openssl.org/source/openssl-1.1.1m.tar.gz
fName=${URL##*/}         # openssl-1.1.1m.tar.gz
fName_base=${fName%.*.*} # openssl-1.1.1m
fName_ext=${fName#*.*.}  # tar.gz
libName=${fName%-*}      # openssl

URL_hash=https://www.openssl.org/source/openssl-1.1.1m.tar.gz.sha256
fName_hash=${URL_hash##*/} # openssl-1.1.1m.tar.gz.sha256

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
find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

# unpacking the archive file
if [ ! -e $BUILD_DIR/$fName_base ]; then
    tar -zxf $CACHE_DIR/$libName/$fName -C $BUILD_DIR # tar.xz
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/bin/$libName ]; then
    cd $BUILD_DIR/$fName_base;
    ./config --prefix=$INST_PATH
    
    make -j
    make install
fi
# ----------------------------------------------- installation: end ---

echo '--------------------------------------------------------------------------------'
echo '------------------------------------------------ end: install openssl/1.1.1m ---'

