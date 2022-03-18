#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: download m4/1.4.15 --------------------------------------------------'

URL=http://ftp.gnu.org/gnu/m4/m4-1.4.15.tar.gz
fName=${URL##*/}         # m4-1.4.15.tar.gz
fName_base=${fName%.*.*} # m4-1.4.15

#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='m4-1.4.15-sha256sum.txt' # xxx-x.x.x-sha256sum.txt

# downloading source file
echo $CPM_CACHE_DIR
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '3d66dfeb609007062265a67b9a2c08d3686a74068830bacae60a6d58413c9367  m4-1.4.15.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi

# check hash
find $CPM_CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CPM_CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: download m4/1.4.15 ---'

