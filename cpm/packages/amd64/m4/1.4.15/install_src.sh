#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh
source ./cpm/set_env.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: install m4/1.4.15 ---------------------------------------------------'

fName='m4-1.4.15.tar.gz'
fName_base=${fName%.*.*} # m4-1.4.15

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
fi

# installation
if [ ! -e $CPM_INST_PATH/bin/m4 ]; then
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

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install m4/1.4.15 ---'

