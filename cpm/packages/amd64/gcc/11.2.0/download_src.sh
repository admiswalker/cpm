#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


URL=http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-11.2.0/gcc-11.2.0.tar.xz
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


URL_hash='http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-11.2.0/sha512.sum'
fName_hash=${URL_hash##*/} # sha512.sum


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
#    echo 'xxxxxxxxxxxxxxxxxxx  gcc-11.2.0.tar.xz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
