#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh
CPM_CALL_DIR=`pwd -P`
. $CPM_INST_PATH/set_env.sh


fName='m4-1.4.15.tar.gz'
fName_base=${fName%.*.*} # m4-1.4.15

# unpacking the src file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -nq $CACHE_DIR/$fName -d $BUILD_DIR
    tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    #tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
    #tar -zxvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.gz
fi

# installation
if [ `cfn_isInstalled` = 'false' ]; then
    cd $CPM_BUILD_DIR/$fName_base;

    # fix installation error
    # - ref: http://programcode.blog.fc2.com/blog-entry-16.html
    cd lib
    sed -i -e '/gets is a security/d' ./stdio.in.h
    cd ..

    ./configure --prefix=$CPM_INST_WDIR --enable-cxx
    make -j
    make check
    make install

    cd $CPM_CALL_DIR
fi
