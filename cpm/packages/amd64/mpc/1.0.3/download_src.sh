#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: download mpc/1.0.3 --------------------------------------------------'

URL=https://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
fName=${URL##*/}         # mpc-1.0.3.tar.gz
fName_base=${fName%.*.*} # mpc-1.0.3

#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='mpc-1.0.3-sha256sum.txt' # xxx-x.x.x-sha256sum.txt

# downloading source file
echo $CACHE_DIR
if [ ! -e $CACHE_DIR/$fName ]; then
    mkdir -p $CACHE_DIR
    cd $CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CACHE_DIR/$fName_hash ]; then
#    wget -P $CACHE_DIR $URL_hash
    echo '617decc6ea09889fb08ede330917a00b16809b8db88c29c31bfbb49cbf88ecc3  mpc-1.0.3.tar.gz' > $CACHE_DIR/$fName_hash
fi

# check hash
find $CACHE_DIR -name $fName_hash -type f -print0 | xargs -0 grep $(sha256sum $CACHE_DIR/$fName) >/dev/null 2>&1
if [ ! $? = 0 ]; then
    echo -e "\e[31mERROR: cmake: hash value of downloaded file is not match.\e[m"
    exit -1
fi

#    '--------------------------------------------------------------------------------'
echo '---------------------------------------------------- end: download mpc/1.0.3 ---'
