#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/libjpeg/v9e/amd64-libjpeg-v9e.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/libjpeg/v9e/amd64-libjpeg-v9e-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-libjpeg-v9e.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libjpeg.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
