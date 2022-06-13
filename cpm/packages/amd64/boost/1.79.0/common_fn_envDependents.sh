#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/boost/1.79.0/amd64-boost-1.79.0.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/boost/1.79.0/amd64-boost-1.79.0-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-boost-1.79.0.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libboost_atomic.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
