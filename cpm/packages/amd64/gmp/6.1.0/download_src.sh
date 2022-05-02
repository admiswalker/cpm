#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://ftp.gnu.org/gnu/gmp/gmp-6.1.0.tar.bz2
fName=${URL##*/}         # gmp-6.1.0.tar.bz2
fName_base=${fName%.*.*} # gmp-6.1.0
libName='gmp'
ver='6.1.0'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='gmp-6.1.0-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '498449a994efeba527885c10405993427995d3f86b8768d8cdf8d9dd7c6b73e8  gmp-6.1.0.tar.bz2' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
