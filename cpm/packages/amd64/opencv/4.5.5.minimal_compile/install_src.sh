#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_INST_PATH/set_env.sh


fName='opencv-4.5.5.tar.gz'
fName_base=${fName%.*.*} # <libName>-<version>
libName=${fName_base%-*} # <libName>
ver=${fName_base#*-}     # <version>

fName_cl='opencv_contrib-4.5.5.tar.gz'
fName_base_cl=${fName_cl%.*.*} # <libName>-<version>


# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    #tar -xf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi
if [ ! -e $CPM_BUILD_DIR/$fName_base_cl ]; then
    #unzip -nq $CPM_CACHE_DIR/$fName -d $CPM_BUILD_DIR
    #tar -xf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    tar -zxvf $CPM_CACHE_DIR/$fName_cl -C $CPM_BUILD_DIR # tar.gz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
#    cd $CPM_BUILD_DIR/$fName_base/
    cd $CPM_BUILD_DIR/

#    mkdir -p build && cd build
#    cmake -D CMAKE_INSTALL_PREFIX=$CPM_INST_WDIR ../opencv-4.5.5
#    cmake --build . --target install
    mkdir -p build && cd build
    cmake -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.5.5/modules -D CMAKE_INSTALL_PREFIX=$CPM_INST_WDIR ../opencv-4.5.5
    make -j
    make install
    
    # gen `replacement_path_for_cpm_archive.txt`
    echo $CPM_INST_WDIR > $CPM_INST_WDIR/replacement_path_for_cpm_archive.txt
    
    cd $CPM_CALL_DIR
fi
