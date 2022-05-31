#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/ninja/1.10.2/amd64-ninja-1.10.2.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/ninja/1.10.2/amd64-ninja-1.10.2-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-ninja-1.10.2.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/bin/ninja ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
