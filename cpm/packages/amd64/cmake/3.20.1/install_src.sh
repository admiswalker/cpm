#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_CALL_DIR/cpm/set_env.sh


libName='cmake'
ver='3.20.1'
cfn_echo_install_begin $libName $ver


fName='cmake-3.20.1.tar.gz'
fName_base=${fName%.*.*} # cmake-3.20.1

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base;
    ./configure --prefix=$CPM_INST_WDIR -- -DCMAKE_USE_OPENSSL=OFF
    
    make -j
    make install
fi


cfn_echo_install_end $libName $ver
