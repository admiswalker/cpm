#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/tags/sstd-2.0.1.tar.gz
fName=${URL##*/}         # <libName>-<version>.tar.gz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


#URL_hash=''
#fName_hash=${URL_hash##*/} # <libName>-<version>-sha256sum.txt
fName_hash=$libName-$ver-sha256sum.txt # <libName>-<version>-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo 'a9ce6f68e1c8bc710d1db9565a97989e29934fa0195eb852b9a76c19200b9cb2  sstd-2.0.1.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
