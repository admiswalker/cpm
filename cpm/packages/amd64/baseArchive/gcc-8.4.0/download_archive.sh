#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: download baseArchive/amd64_gcc-8.4.0 --------------------------------'

mkdir -p $CACHE_DIR

URL1=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64_gcc-8.4.0.tar.xz-00
URL2=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64_gcc-8.4.0.tar.xz-01
fName1=${URL1##*/}      # local_amd64_gcc-8.4.0.tar.xz-00
fName2=${URL2##*/}      # local_amd64_gcc-8.4.0.tar.xz-01
fName='amd64_gcc-8.4.0.tar.xz'
#fName_base=${fName%.*} #
#fName_ext=${fName#*.}  #
#libName=${fName%-*}    #
libName='gcc-8.4.0'

URL_hash=https://github.com/admiswalker/cpm_baseArchive/raw/main/base_archive/amd64/gcc/8.4.0/amd64_gcc-8.4.0-sha256sum.txt
fName_hash=${URL_hash##*/} # cmake-3.20.1-SHA-256.txt

# downloading source file
if [ ! -e $CACHE_DIR/$libName/$fName1 ]; then
    wget -P $CACHE_DIR/$libName $URL1
fi
if [ ! -e $CACHE_DIR/$libName/$fName2 ]; then
    wget -P $CACHE_DIR/$libName $URL2
fi
if [ ! -e $CACHE_DIR/$libName/$fName ]; then
    cat $CACHE_DIR/$libName/$fName-* >> $CACHE_DIR/$libName/$fName
fi
if [ ! -e $CACHE_DIR/$libName/$fName_hash ]; then
    wget -P $CACHE_DIR/$libName $URL_hash
fi

# check hash
find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName1) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi
find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName2) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi
find $CACHE_DIR/$libName -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$libName/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo 'ERROR: cmake: hash value of downloaded file is not match.'
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------- end: download baseArchive/amd64_gcc-8.4.0 ---'

