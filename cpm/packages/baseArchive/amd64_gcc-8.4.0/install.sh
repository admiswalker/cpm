#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

echo '--- begin: install baseArchive/amd64_gcc-8.4.0 ---------------------------------'

mkdir -p $CACHE_DIR
mkdir -p $BUILD_DIR
mkdir -p $INST_PATH

URL1=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64_gcc-8.4.0.tar.xz-00
URL2=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64_gcc-8.4.0.tar.xz-01
fName1=${URL1##*/}      # local_amd64_gcc-8.4.0.tar.xz-00
fName2=${URL2##*/}      # local_amd64_gcc-8.4.0.tar.xz-01
fName='amd64_gcc-8.4.0.tar.xz'
#fName_base=${fName%.*} #
#fName_ext=${fName#*.}  #
#libName=${fName%-*}    #


# installing depending packages


# downloading source file
if [ ! -e $CACHE_DIR/$fName1 ]; then
    wget -P $CACHE_DIR $URL1
fi
if [ ! -e $CACHE_DIR/$fName2 ]; then
    wget -P $CACHE_DIR $URL2
fi
if [ ! -e $CACHE_DIR/$fName ]; then
    cat $CACHE_DIR/$fName-* >> $CACHE_DIR/$fName
fi

# unpacking the archive file


# --- installation: begin ---------------------------------------------
if [ ! -e $INST_PATH/bin/gcc ]; then
    tar -Jxf $CACHE_DIR/$fName -C $INST_PATH
fi
# ----------------------------------------------- installation: end ---

echo '----------------------------------- end: install baseArchive/amd64_gcc-8.4.0 ---'

