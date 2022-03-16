#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: download gmp/6.1.0 --------------------------------------------------'

URL=https://ftp.gnu.org/gnu/gmp/gmp-6.1.0.tar.bz2
fName=${URL##*/}         # gmp-6.1.0.tar.bz2
fName_base=${fName%.*.*} # gmp-6.1.0

#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='gmp-6.1.0-sha256sum.txt' # xxx-x.x.x-sha256sum.txt

# downloading source file
echo $CACHE_DIR
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '498449a994efeba527885c10405993427995d3f86b8768d8cdf8d9dd7c6b73e8  gmp-6.1.0.tar.bz2' > $CACHE_DIR/$fName_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
    return -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: download gmp/6.1.0 ---'

