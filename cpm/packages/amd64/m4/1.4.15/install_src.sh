#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_CALL_DIR/cpm/set_env.sh


libName='m4'
ver='1.4.15'
cfn_echo_install_begin $libName $ver


fName='m4-1.4.15.tar.gz'
fName_base=${fName%.*.*} # m4-1.4.15

# unpacking the src file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
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


cfn_echo_install_end $libName $ver
