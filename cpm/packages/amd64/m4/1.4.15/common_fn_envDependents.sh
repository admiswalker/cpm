#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/m4/1.4.15/amd64-m4-1.4.15.tar.xz

    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/m4/1.4.15/amd64-m4-1.4.15-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-m4-1.4.15.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/bin/m4 ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
