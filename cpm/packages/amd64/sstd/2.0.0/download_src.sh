#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


URL=https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/refs/tags/v2.0.0.zip
#fName=${URL##*/}         # mpfr-3.1.4.tar.bz2
#fName_base=${fName%.*.*} # mpfr-3.1.4.tar.bz2
fName='sstd-2.0.0.zip'
fName_base='sstd-2.0.0'
libName='sstd'
ver='2.0.0'


#URL_hash=''
#fName_hash=${URL_hash##*/} # xxx-x.x.x-sha256sum.txt
fName_hash='sstd-2.0.0-sha256sum.txt' # xxx-x.x.x-sha256sum.txt


cfn_echo_download_begin $libName $ver


# downloading source file
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    mkdir -p $CPM_CACHE_DIR
    cd $CPM_CACHE_DIR; wget -O $fName $URL
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
#    wget -P $CPM_CACHE_DIR $URL_hash
    echo '4cfdc202eb04a28d4a3bea76dc01dee6ffea6b2617162db28391ae3ae79351cf  sstd-2.0.0.zip' > $CPM_CACHE_DIR/$fName_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
