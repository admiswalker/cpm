#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: download sstd/latest ------------------------------------------------'

URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/heads/master.zip
#fName=${URL##*/}         # master.zip
#fName_base=${fName%.*.*} # master
fName='sstd-latest.tar.gz'
fName_base='sstd-latest'

#URL_hash=''
#fName_hash=${URL_hash##*/} # sstd-latest.tar.gz

# downloading source file
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
#if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
#fi

# check hash
#find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
#if [ ! $? = 0 ]; then
#    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
#    return -1
#fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------------- end: download sstd/latest ---'

