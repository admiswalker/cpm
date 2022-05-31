#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=ftp://sourceware.org/pub/libffi/libffi-3.2.1.tar.gz
fName=${URL##*/}         # <libName>-<version>.tar.xz
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


#URL_hash='https://download.gnome.org/sources/glib/2.31/glib-2.31.8.sha256sum'
#fName_hash=${URL_hash##*/} # sha512.sum
fName_hash=sha256.sum


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi

if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo 'd06ebb8e1d9a22d19e38d63fdb83954253f39bedc5d46232a05645685722ca37  libffi-3.2.1.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
