#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: download mpfr/3.1.4 -------------------------------------------------'

URL=https://ftp.gnu.org/gnu/mpfr/mpfr-3.1.4.tar.bz2
fName=${URL##*/}         # mpfr-3.1.4.tar.bz2
fName_base=${fName%.*.*} # mpfr-3.1.4.tar.bz2

#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='mpfr-3.1.4-sha256sum.txt' # xxx-x.x.x-sha256sum.txt

# downloading source file
echo $CACHE_DIR
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo 'd3103a80cdad2407ed581f3618c4bed04e0c92d1cf771a65ead662cc397f7775  mpfr-3.1.4.tar.bz2' > $CACHE_DIR/$fName_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '--------------------------------------------------- end: download mpfr/3.1.4 ---'

