#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://gcc.gnu.org/pub/gcc/infrastructure/isl-0.18.tar.bz2
fName=${URL##*/}         # isl-0.18.tar.bz2
fName_base=${fName%.*.*} # isl-0.18.tar.bz2
libName='isl'
ver='0.18'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='isl-0.18-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo '6b8b0fd7f81d0a957beb3679c81bbb34ccc7568d5682844d8924424a0dadcb1b  isl-0.18.tar.bz2' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
