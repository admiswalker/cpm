#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
BUILD_DIR=$CALL_DIR/$BUILD_DIR; mkdir -p $BUILD_DIR # When using Docker, the absolute path is determined at run time.
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: install m4/1.4.15 ---------------------------------------------------'

fName='m4-1.4.15.tar.gz'
fName_base=${fName%.*.*} # m4-1.4.15

# unpacking the archive file
if [ ! -e $BUILD_DIR/googletest-release-1.11.0 ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CACHE_DIR/$fName -C $BUILD_DIR # tar.xz
fi

# installation
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    cd $BUILD_DIR/$fName_base;

    # fix installation error
    # - ref: http://programcode.blog.fc2.com/blog-entry-16.html
    cd lib
    sed -i -e '/gets is a security/d' ./stdio.in.h
    cd ..

    ./configure --prefix=$INST_PATH --enable-cxx
    make -j
    make check
    make install

    cd $CALL_DIR
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install m4/1.4.15 ---'

