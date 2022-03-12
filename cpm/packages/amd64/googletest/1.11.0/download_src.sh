#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR; mkdir -p $CACHE_DIR # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: download googletest/1.11.0 ------------------------------------------'

URL=https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
#fName=${URL##*/}         # release-1.11.0.tar.gz
#fName_base=${fName%.*.*} # release-1.11.0
fName='googletest-1.11.0.tar.gz'
fName_base='googletest-1.11.0'

#URL_hash=''
#fName_hash=${URL_hash##*/} # googletest-1.11.0-sha256sum.txt
fName_hash='googletest-1.11.0-sha256sum.txt'

# downloading source file
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo 'b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5  release-1.11.0.tar.gz' > $CACHE_DIR/$fName_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------- end: download googletest/1.11.0 ---'

