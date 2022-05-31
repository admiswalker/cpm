#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=http://pkgconfig.freedesktop.org/releases/pkg-config-0.29.2.tar.gz
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


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
    echo '6fc69c01688c9458a57eb9a1664c9aba372ccda420a02bf4429fe610e7e7d591  pkg-config-0.29.2.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
