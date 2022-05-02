#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1.tar.gz
fName=${URL##*/}         # isl-0.18.tar.bz2
fName_base=${fName%.*.*} # isl-0.18.tar.bz2
libName='cmake'
ver='3.20.1'


URL_hash=https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-SHA-256.txt
fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    wget -P $CPM_CACHE_DIR $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
fi
cfn_check_hash_value
