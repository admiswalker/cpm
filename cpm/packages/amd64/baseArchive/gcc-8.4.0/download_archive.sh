#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: download baseArchive/gcc-8.4.0 --------------------------------------'

URL1=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0.tar.xz-00
URL2=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0.tar.xz-01
fName1=${URL1##*/}       # amd64-gcc-8.4.0.tar.xz-00
fName2=${URL2##*/}       # amd64-gcc-8.4.0.tar.xz-01
fName=${fName1%-00}      # amd64-gcc-8.4.0.tar.xz
fName_base=${fName%.*.*} # amd64-gcc-8.4.0

URL_hash=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0-sha256sum.txt
fName_hash=${URL_hash##*/} # amd64-gcc-8.4.0-sha256sum.txt

# downloading source file
if [ ! -e $CACHE_DIR/$fName1 ]; then
    wget -P $CACHE_DIR $URL1
fi
if [ ! -e $CACHE_DIR/$fName2 ]; then
    wget -P $CACHE_DIR $URL2
fi
if [ ! -e $CACHE_DIR/$fName ]; then
    cat $CACHE_DIR/$fName-* >> $CACHE_DIR/$fName
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
    wget -P $CACHE_DIR $URL_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName1) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName2) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------------- end: download baseArchive/gcc-8.4.0 ---'

