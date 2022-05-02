#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/set_env.sh


fName='gcc-11.2.0.tar.xz'
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
    
    unset LIBRARY_PATH CPATH C_INCLUDE_PATH PKG_CONFIG_PATH CPLUS_INCLUDE_PATH INCLUDE
    
    export LD_LIBRARY_PATH=$CPM_DLIB_PATH/lib

    #./configure --prefix=$INST_PATH --enable-cxx --disable-multilib --enable-languages=c,c++
    #./configure --disable-bootstrap --disable-multilib --enable-languages=c,c++,fortran --prefix=$INST_PATH --with-gmp=$INST_PATH --with-mpc=$INST_PATH --with-mpfr=$INST_PATH --with-isl=$INST_PATH
    ./configure --disable-multilib --enable-languages=c,c++ --prefix=$CPM_INST_WDIR --with-gmp=$CPM_DLIB_PATH --with-mpc=$CPM_DLIB_PATH --with-mpfr=$CPM_DLIB_PATH --with-isl=$CPM_DLIB_PATH
    make -j
    make check
    make install

    # gen `replacement_path_for_cpm_archive.txt`
    echo $CPM_INST_WDIR > $CPM_INST_WDIR/replacement_path_for_cpm_archive.txt
    
    cd $CPM_CALL_DIR
fi
