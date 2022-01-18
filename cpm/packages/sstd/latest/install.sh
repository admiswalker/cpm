#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

echo '--- begin: install sstd/1.0.0 --------------------------------------------------'
echo '--------------------------------------------------------------------------------'

mkdir -p $CACHE_DIR
mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/heads/master.zip
fName=${URL##*/}       # master.zip
fName_base=${fName%.*} # master
fName_ext=${fName#*.}  # zip
#libName=${fName%-*}   # release
libName=sstd-latest    # sstd-latest

URL_hash=''
fName_hash=${URL_hash##*/} # openssl-1.1.1m.tar.gz.sha256

# installing depending packages
# - gcc-8.4.0 as a base compiler
# - cmake

# downloading source file
if [ ! -e $CACHE_DIR/$libName/$fName ]; then
    wget -P $CACHE_DIR/$libName $URL
fi

# check hash
#find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName) >/dev/null 2>&1
#if [ ! $? = 0 ]; then
#    echo 'ERROR: cmake: hash value of downloaded file is not match.'
#    return -1
#fi

# unpacking the archive file
if [ ! -e $BUILD_DIR/SubStandardLibrary-SSTD--master ]; then
    unzip -n $CACHE_DIR/$libName/$fName -d $BUILD_DIR # zip
    #tar -zxf $CACHE_DIR/$libName/$fName -C $BUILD_DIR # tar.xz
fi

# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/lib/libsstd.a ]; then
    cd $BUILD_DIR/SubStandardLibrary-SSTD--master/sstd;
    
    make -j
    
    cp -r lib/* -t $INST_PATH/lib
    cp -r include/* -t $INST_PATH/include
fi
# ----------------------------------------------- installation: end ---

echo '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: install sstd/1.0.0 ---'

