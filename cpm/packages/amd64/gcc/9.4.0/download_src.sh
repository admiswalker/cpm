#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-9.4.0/gcc-9.4.0.tar.xz
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


URL_hash='http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-9.4.0/sha512.sum'
fName_hash=${URL_hash##*/} # sha512.sum


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
#    echo 'xxxxxxxxxxxxxxxxxxx  gcc-9.4.0.tar.xz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
