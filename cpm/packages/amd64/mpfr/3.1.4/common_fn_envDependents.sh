#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/mpfr/3.1.4/amd64-mpfr-3.1.4.tar.xz

    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/mpfr/3.1.4/amd64-mpfr-3.1.4-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-mpfr-3.1.4.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libmpfr.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
