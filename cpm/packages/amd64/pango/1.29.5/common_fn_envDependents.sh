#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/pango/1.29.5/amd64-pango-1.29.5.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/pango/1.29.5/amd64-pango-1.29.5-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-pango-1.29.5.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/bin/pango-querymodules ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
