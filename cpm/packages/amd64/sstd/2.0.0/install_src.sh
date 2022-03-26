#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_CALL_DIR/cpm/set_env.sh


libName='sstd'
ver='2.0.0'
cfn_echo_install_begin $libName $ver


fName='sstd-2.0.0.zip'
fName_base=${fName%.*.*} # mpfr-3.1.4

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    #tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    #tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/SubStandardLibrary-SSTD--2.0.0/sstd;
    
    make -j

    mkdir -p $CPM_INST_WDIR/lib
    mkdir -p $CPM_INST_WDIR/include
    cp -r lib/* -t $CPM_INST_WDIR/lib
    cp -r include/* -t $CPM_INST_WDIR/include
fi


cfn_echo_install_end $libName $ver
