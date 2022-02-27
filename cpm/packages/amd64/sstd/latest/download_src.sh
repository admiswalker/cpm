#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: download sstd/latest ------------------------------------------------'

mkdir -p $CACHE_DIR

URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/heads/master.zip
#fName=${URL##*/}         # master.zip
#fName_base=${fName%.*.*} # master
fName='sstd-latest.tar.gz'
fName_base='sstd-latest'

#URL_hash=''
#fName_hash=${URL_hash##*/} # sstd-latest.tar.gz

CACHE_BASE=$CACHE_DIR/src/$fName_base

# downloading source file
if [ ! -e $CACHE_BASE/$fName ]; then
    mkdir -p $CACHE_BASE
    cd $CACHE_BASE; wget -O $fName $URL
fi
#if [ ! -e $CACHE_BASE/$fName_hash ]; then
#    wget -P $CACHE_BASE $URL_hash
#fi

# check hash
#find $CACHE_BASE -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_BASE/$fName) >/dev/null 2>&1
#if [ ! $? = 0 ]; then
#    echo 'ERROR: cmake: hash value of downloaded file is not match.'
#    return -1
#fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------------- end: download sstd/latest ---'

