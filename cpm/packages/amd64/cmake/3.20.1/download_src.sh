#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: download cmake/3.20.1 -----------------------------------------------'

URL=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1.tar.gz
fName=${URL##*/}         # cmake-3.20.1.tar.gz
fName_base=${fName%.*.*} # cmake-3.20.1

URL_hash=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-SHA-256.txt
fName_hash=${URL_hash##*/} # cmake-3.20.1-SHA-256.txt

# downloading source file
if [ ! -e $CACHE_DIR/$fName ]; then
    wget -P $CACHE_DIR $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
    wget -P $CACHE_DIR $URL_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '------------------------------------------------- end: download cmake/3.20.1 ---'

