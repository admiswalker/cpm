#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh
source ./cpm/set_env.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: install gmp/6.1.0 ---------------------------------------------------'

fName='gmp-6.1.0.tar.bz2'
fName_base=${fName%.*.*} # m4-1.4.15

# unpacking the archive file
if [ ! -e $BUILD_DIR/$fName_base ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    #tar -zxf $CACHE_DIR/$fName -C $BUILD_DIR # tar.xz
    tar -xvf $CACHE_DIR/$fName -C $BUILD_DIR # tar.bz2
fi

# installation
if [ ! -e $INST_PATH/lib/libgmp.a ]; then
    cd $BUILD_DIR/$fName_base
    
    PATH=$PATH:$INed_PATH/bin
    
    ./configure --prefix=$INST_PATH --enable-cxx
    make -j
    make check
    make install

    # gen `replacement_path_for_cpm_archive.txt`
    echo $INST_PATH > replacement_path_for_cpm_archive.txt

    cd $CALL_DIR
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install gmp/6.1.0 ---'

