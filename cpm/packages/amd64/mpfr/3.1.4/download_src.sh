#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://ftp.gnu.org/gnu/mpfr/mpfr-3.1.4.tar.bz2
fName=${URL##*/}         # mpfr-3.1.4.tar.bz2
fName_base=${fName%.*.*} # mpfr-3.1.4.tar.bz2
libName='mpfr'
ver='3.1.4'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='mpfr-3.1.4-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo 'd3103a80cdad2407ed581f3618c4bed04e0c92d1cf771a65ead662cc397f7775  mpfr-3.1.4.tar.bz2' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
