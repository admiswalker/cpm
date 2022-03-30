#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=https://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
fName=${URL##*/}         # mpc-1.0.3.tar.gz
fName_base=${fName%.*.*} # mpc-1.0.3
libName='mpc'
ver='1.0.3'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='mpc-1.0.3-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo '617decc6ea09889fb08ede330917a00b16809b8db88c29c31bfbb49cbf88ecc3  mpc-1.0.3.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
