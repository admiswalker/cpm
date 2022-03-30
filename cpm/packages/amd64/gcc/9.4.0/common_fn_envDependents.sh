#!/bin/bash


cfn_set_archive_URL(){
    URL00=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/9.4.0/amd64-gcc-9.4.0.tar.xz-00
    URL01=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/9.4.0/amd64-gcc-9.4.0.tar.xz-01

    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/gcc/9.4.0/amd64-gcc-9.4.0-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-gcc-9.4.0.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/gcc ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
