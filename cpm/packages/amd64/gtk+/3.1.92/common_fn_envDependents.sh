#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/sstd/2.0.1/amd64-pkg-config-0.29.2.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/sstd/2.0.1/amd64-pkg-config-0.29.2-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-sstd-2.0.1.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/bin/gtk+ ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
