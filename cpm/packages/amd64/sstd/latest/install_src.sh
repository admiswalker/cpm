#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/set_env.sh


fName='sstd-latest.zip'
fName_base='sstd-latest'

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/SubStandardLibrary-SSTD--master ]; then
    unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR # zip
    #tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/SubStandardLibrary-SSTD--master/sstd;
    
    make -j
    
    mkdir -p $CPM_INST_WDIR/lib
    mkdir -p $CPM_INST_WDIR/include
    
    cp -r lib/* -t $CPM_INST_WDIR/lib
    cp -r include/* -t $CPM_INST_WDIR/include
fi
