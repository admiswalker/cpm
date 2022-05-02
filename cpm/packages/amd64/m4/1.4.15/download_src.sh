#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=http://ftp.gnu.org/gnu/m4/m4-1.4.15.tar.gz
fName=${URL##*/}
libName='m4'
ver='1.4.15'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='m4-1.4.15-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '3d66dfeb609007062265a67b9a2c08d3686a74068830bacae60a6d58413c9367  m4-1.4.15.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
