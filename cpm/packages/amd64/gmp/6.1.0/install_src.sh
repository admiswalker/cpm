#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh
source ./cpm/set_env.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: install gmp/6.1.0 ---------------------------------------------------'

fName='gmp-6.1.0.tar.bz2'
fName_base=${fName%.*.*} # gmp-6.1.0

# unpacking the archive file
if [ ! -e $CPM_BUILD_DIR/$fName_base ]; then
    #unzip -n $CPM_CACHE_DIR/$libName/$fName -d $CPM_BUILD_DIR
    #tar -zxf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.xz
    tar -xvf $CPM_CACHE_DIR/$fName -C $CPM_BUILD_DIR # tar.bz2
fi

# installation
if [ ! -e $CPM_INST_PATH/lib/libgmp.a ]; then
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

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install gmp/6.1.0 ---'
