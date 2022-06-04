#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/libpng/1.6.37/amd64-libpng-1.6.37.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/libpng/1.6.37/amd64-libpng-1.6.37-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-libpng-1.6.37.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libpng.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
