#!/bin/bash

CPM_CALL_DIR=`pwd -P`
. $CPM_CALL_DIR/cpm/init_path_and_dir.sh
. $CPM_OWN_DIR/common_fn.sh


URL00=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0.tar.xz-00
URL01=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0.tar.xz-01

URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/7.5.0/amd64-gcc-7.5.0-sha256sum.txt

# SET: fName, fName_base, arcName, libName, ver
fName=''
if [ $URL != 0 ]; then
    fName=${URL##*/}     # <architecture>-<libName>-<version>.tar.xz
elif [ $URL00 != 0 ]; then
    fName00=${URL00##*/} # <architecture>-<libName>-<version>.tar.xz-00
    fName=${fName00%-00} # <architecture>-<libName>-<version>.tar.xz
fi
fName_base=${fName%.*.*} # <architecture>-<libName>-<version>
tmp=${fName%-*}          # <architecture>-<libName>
arcName=${tmp%-*}        # <architecture>
libName=${tmp#*-}        # <libName>
ver=${fName_base#*-*-}   # <version>
fName_hash=${URL_hash##*/} # <architecture>-<libName>-<version>-sha256sum.txt


cfn_echo_download_begin $libName $ver


# downloading source file
for i in `seq 0 99`
do
    num=`printf "%02d\n" $i`
    
    URL_xx=URL$num
    cmd_u='echo $'$URL_xx
    URL_str=`eval $cmd_u`
    URL_len=${#URL_str}

    if [ $URL_len == 0 ]; then
	break
    fi
    
    fName_xx=${URL_str##*/} # <architecture>-<libName>-<version>.tar.xz-xx
    if [ ! -e $CPM_CACHE_DIR/$fName_xx ]; then
	wget -P $CPM_CACHE_DIR $URL_str
    fi
done
if [ ! -e $CPM_CACHE_DIR/$fName ]; then
    cat $CPM_CACHE_DIR/$fName-* >> $CPM_CACHE_DIR/$fName
fi
if [ ! -e $CPM_CACHE_DIR/$fName_hash ]; then
    wget -P $CPM_CACHE_DIR $URL_hash
fi
cfn_check_hash_value


cfn_echo_download_end $libName $ver
