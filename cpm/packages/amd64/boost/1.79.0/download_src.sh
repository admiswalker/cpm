#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.bz2
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


#URL_hash=''
#fName_hash=${URL_hash##*/} # sha512.sum
fName_hash=sha256.sum


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi

if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo '475d589d51a7f8b3ba2ba4eda022b170e562ca3b760ee922c146b6c65856ef39  boost_1_79_0.tar.bz2' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
