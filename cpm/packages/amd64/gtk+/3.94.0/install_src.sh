#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_INST_PATH/set_env.sh


fName='gtk+-3.94.0.tar.xz'
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>


# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    tar -xf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    #tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base/

    #export PKG_CONFIG_PATH=$CPM_INST_PATH/lib/pkgconfig
    #./configure --prefix=$CPM_INST_WDIR
    meson --prefix=$CPM_INST_WDIR --pkg-config-path=$CPM_INST_PATH/lib/pkgconfig:$CPM_INST_PATH/lib/x86_64-linux-gnu/pkgconfig -Dgst-plugins-good:cairo=enabled _build .
    cd _build
    ninja
    
    #make -j
    #make install
    
    cd $CPM_CALL_DIR
fi
