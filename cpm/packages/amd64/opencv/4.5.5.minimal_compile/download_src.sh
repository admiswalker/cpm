#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://github.com/opencv/opencv/archive/4.5.5.tar.gz
#fName=${URL##*/}           # <libName>-<version>.tar.xz
fName='opencv-4.5.5.tar.gz' # <libName>-<version>.tar.xz
fName_base=${fName%.*.*}    # <libName>-<version>
libName=${fName_base%-*}    # <libName>
ver=${fName_base#*-}        # <version>


URL_cl=https://github.com/opencv/opencv_contrib/archive/4.5.5.tar.gz
fName_cl='opencv_contrib-4.5.5.tar.gz' # <libName>-<version>.tar.xz


#URL_hash='http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-12.1.0/sha512.sum'
#fName_hash=${URL_hash##*/} # sha512.sum
fName_hash=sha256.sum


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_cl ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName_cl $URL_cl
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo 'a1cfdcf6619387ca9e232687504da996aaa9f7b5689986b8331ec02cb61d28ad  opencv-4.5.5.tar.gz' > $CPM_CACHE_DIR/$fName_hash
    echo 'a97c2eaecf7a23c6dbd119a609c6d7fae903e5f9ff5f1fe678933e01c67a6c11  opencv_contrib-4.5.5.tar.gz' >> $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
