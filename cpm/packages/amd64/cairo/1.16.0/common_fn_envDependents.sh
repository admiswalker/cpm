#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/cairo/1.16.0/amd64-cairo-1.16.0.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/cairo/1.16.0/amd64-cairo-1.16.0-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-cairo-1.16.0.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libcairo.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
