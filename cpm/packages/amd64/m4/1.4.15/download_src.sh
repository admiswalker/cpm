#!/bin/bash
echo CACHE_DIR
echo $CACHE_DIR
echo BUILD_DIR
echo $BUILD_DIR
echo INST_PATH
echo $INST_PATH
exit 0

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: download m4/1.4.15 --------------------------------------------------'

CALL_DIR=`pwd -P`
CACHE_DIR=$CALL_DIR/$CACHE_DIR

mkdir -p $CACHE_DIR

URL=http://ftp.gnu.org/gnu/m4/m4-1.4.15.tar.gz
fName=${URL##*/}         # m4-1.4.15.tar.gz
fName_base=${fName%.*.*} # m4-1.4.15

#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='m4-1.4.15-sha256sum.txt' # xxx-x.x.x-sha256sum.txt

# downloading source file
echo $CACHE_DIR
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '3d66dfeb609007062265a67b9a2c08d3686a74068830bacae60a6d58413c9367  m4-1.4.15.tar.gz' > $CACHE_DIR/$fName_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: download m4/1.4.15 ---'

