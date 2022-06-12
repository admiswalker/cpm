#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://cairographics.org/releases/cairo-1.14.12.tar.xz
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


URL_hash='https://cairographics.org/releases/cairo-1.14.12.tar.xz.sha1'
fName_hash=${URL_hash##*/} # sha512.sum
#fName_hash=sha256.sum


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi

if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
#    echo 'xxxxxxxxxxxxxx  xxxxx-0.0.0.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
