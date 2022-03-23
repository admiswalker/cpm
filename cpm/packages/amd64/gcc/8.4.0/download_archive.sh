#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


URL1=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0.tar.xz-00
URL2=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0.tar.xz-01
fName1=${URL1##*/}       # amd64-gcc-8.4.0.tar.xz-00
fName2=${URL2##*/}       # amd64-gcc-8.4.0.tar.xz-01

fName=${fName1%-00}       # <architecture>-<libName>-<version>.tar.xz
fName_base=${fName%.*.*}  # <architecture>-<libName>-<version>
tmp=${fName%-*}           # <architecture>-<libName>
arcName=${tmp%-*}         # <architecture>
libName=${tmp#*-}         # <libName>
ver=${fName_base#*-*-}    # <version>


URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/8.4.0/amd64-gcc-8.4.0-sha256sum.txt
fName_hash=${URL_hash##*/} # amd64-m4-1.4.15-sha256sum.txt


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName1 ]; then
    wget -P $CPM_CACHE_DIR $URL1
fi
if [ ! -e $CPM_CACHE_DIR/$fName2 ]; then
    wget -P $CPM_CACHE_DIR $URL2
fi
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    cat $CPM_CACHE_DIR/$fName-* >> $CPM_CACHE_DIR/$fName
fi

if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
