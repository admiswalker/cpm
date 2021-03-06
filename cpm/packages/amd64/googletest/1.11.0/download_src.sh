#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
#fName=${URL##*/}         # release-1.11.0.tar.gz
#fName_base=${fName%.*.*} # release-1.11.0
fName='googletest-1.11.0.tar.gz'
fName_base='googletest-1.11.0'
libName='googletest'
ver='1.11'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha26sum.txt
fName_hash='googletest-1.11.0-sha256sum.txt'


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo 'b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5  googletest-1.11.0.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value
