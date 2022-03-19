#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/heads/master.zip
#fName=${URL##*/}         # master.zip
#fName_base=${fName%.*.*} # master
fName='sstd-latest.zip'
fName_base='sstd-latest'
libName='sstd'
ver='latest'


#URL_hash=''
#fName_hash=${URL_hash##*/} # sstd-latest.tar.gz


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
#if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    echo '3d66dfeb609007062265a67b9a2c08d3686a74068830bacae60a6d58413c9367  m4-1.4.15.tar.gz' > $CPM_CACHE_DIR/$fName_hash
#fi
#cfn_check_hash_value


cfn_echo_download_end $libName $ver
