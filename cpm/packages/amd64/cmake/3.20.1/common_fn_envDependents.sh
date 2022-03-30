#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/cmake/3.20.1/amd64-cmake-3.20.1.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/cmake/3.20.1/amd64-cmake-3.20.1-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-cmake-3.20.1.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/bin/cmake ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
