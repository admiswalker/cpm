#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh
source ./cpm/set_env.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: install mpc/1.0.3 ---------------------------------------------------'

fName='mpc-1.0.3.tar.gz'
fName_base=${fName%.*.*} # mpc-1.0.3.tar.gz
libName=${fName%-*}      # mpc

# unpacking the archive file
if [ ! -e $BUILD_DIR/$fName_base ]; then
    #unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR
    tar -zxf $CACHE_DIR/$fName -C $BUILD_DIR # tar.xz
    #tar -xvf $CACHE_DIR/$fName -C $BUILD_DIR # tar.bz2
fi

# installation
if [ ! -e $INST_PATH/lib/lib$libName.a ]; then
    cd $BUILD_DIR/$fName_base
    
    ./configure --prefix=$INST_PATH --with-gmp=$INed_PATH --with-mpfr=$INed_PATH
    make -j
    make check
    make install

    cd $CALL_DIR
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install mpc/1.0.3 ---'

