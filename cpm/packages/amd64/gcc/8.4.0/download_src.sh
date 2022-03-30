#!/bin/bash

CPM_OWN_DIR=`dirname $0`
. $CPM_OWN_DIR/init_path.sh
. $CPM_OWN_DIR/common_fn.sh
. $CPM_OWN_DIR/common_fn_envDependents.sh


URL=http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-8.4.0/gcc-8.4.0.tar.gz
fName=${URL##*/}         # mpfr-3.1.4.tar.bz2
fName_base=${fName%.*.*} # mpfr-3.1.4.tar.bz2
libName='gcc'
ver='8.4.0'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='gcc-8.4.0-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo '41e8b145832fc0b2b34c798ed25fb54a881b0cee4cd581b77c7dc92722c116a8  gcc-8.4.0.tar.gz' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
