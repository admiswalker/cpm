#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/blob/main/archive/amd64/libxml2/2.9.9/amd64-libxml2-2.9.9.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/blob/main/archive/amd64/libxml2/2.9.9/amd64-libxml2-2.9.9-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-libxml2-2.9.9.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libxml2.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
