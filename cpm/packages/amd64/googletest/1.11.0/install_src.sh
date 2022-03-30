#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/set_env.sh


libName='googletest'
ver='1.11.0'
cfn_echo_install_begin $libName $ver


fName='googletest-1.11.0.tar.gz'
fName_base=${fName%.*.*} # mpfr-3.1.4

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    #tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/googletest-release-1.11.0;
    mkdir -p build; cd build; cmake ..; make
    
    mkdir -p $CPM_INST_WDIR/lib
    mkdir -p $CPM_INST_WDIR/include
    
    cp -r lib/* -t $CPM_INST_WDIR/lib
    cd ../googletest; cp -r include/* -t $CPM_INST_WDIR/include
fi


cfn_echo_install_end $libName $ver
