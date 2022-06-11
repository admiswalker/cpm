#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/glib/2.73.0/amd64-glib-2.73.0.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/glib/2.73.0/amd64-glib-2.73.0-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-glib-2.73.0.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/x86_64-linux-gnu/libgio-2.0.so ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
