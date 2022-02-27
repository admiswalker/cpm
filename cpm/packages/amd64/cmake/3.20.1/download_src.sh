#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: download cmake/3.20.1 -----------------------------------------------'

mkdir -p $CACHE_DIR

URL=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1.tar.gz
fName=${URL##*/}         # cmake-3.20.1.tar.gz
fName_base=${fName%.*.*} # cmake-3.20.1

URL_hash=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-SHA-256.txt
fName_hash=${URL_hash##*/} # cmake-3.20.1-SHA-256.txt

CACHE_BASE=$CACHE_DIR/src/$fName_base

# downloading source file
if [ ! -e $CACHE_BASE/$fName ]; then
    wget -P $CACHE_BASE $URL
fi
if [ ! -e $CACHE_BASE/$fName_hash ]; then
    wget -P $CACHE_BASE $URL_hash
fi

# check hash
find $CACHE_BASE -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_BASE/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '------------------------------------------------- end: download cmake/3.20.1 ---'

