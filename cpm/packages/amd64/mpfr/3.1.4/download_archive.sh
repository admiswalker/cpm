#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: download mpfr/3.1.4 -------------------------------------------------'

URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/mpfr/3.1.4/amd64-mpfr-3.1.4.tar.xz
fName=${URL##*/}         # amd64-mpfr-3.1.4.tar.xz
fName_base=${fName%.*.*} # amd64-mpfr-3.1.4

URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/mpfr/3.1.4/amd64-mpfr-3.1.4-sha256sum.txt
fName_hash=${URL_hash##*/} # amd64-mpfr-3.1.4-sha256sum.txt

# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    wget -P $CPM_CACHE_DIR $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
fi

# check hash
find $CPM_CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CPM_CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '--------------------------------------------------- end: download mpfr/3.1.4 ---'
