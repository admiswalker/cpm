#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_CALL_DIR/cpm/set_env.sh


libName='gmp'
ver='6.1.0'
cfn_echo_install_begin $libName $ver


fName='gmp-6.1.0.tar.bz2'
fName_base=${fName%.*.*} # gmp-6.1.0

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -n $CPM_CACHE_DIR/$libName/$fName -d $CPM_BUILD_DIR
    #tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base
    
    PATH=$PATH:$CPM_DLIB_PATH/bin
    
    ./configure --prefix=$CPM_INST_WDIR --enable-cxx
    make -j
    make check
    make install

    # gen `replacement_path_for_cpm_archive.txt`
    echo $CPM_INST_WDIR > $CPM_INST_WDIR/replacement_path_for_cpm_archive.txt

    cd $CPM_CALL_DIR
fi


cfn_echo_install_end $libName $ver
