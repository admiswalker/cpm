#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


fName='amd64-sstd-1.0.0.tar.xz'
fName_base=${fName%.*.*}  # <architecture>-<libName>-<version>
tmp=${fName%-*}           # <architecture>-<libName>
arcName=${tmp%-*}         # <architecture>
libName=${tmp#*-}         # <libName>
ver=${fName_base#*-*-}    # <version>


cfn_echo_install_begin $libName $ver


# installation
if [ `cfn_isInstalled` = 'false' ]; then
    tar -Jxf $CPM_CACHE_DIR/$fName -C $CPM_INST_WDIR # tar.xz
fi


cfn_echo_install_end $libName $ver
