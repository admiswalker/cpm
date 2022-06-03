#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/freetype/2.12.1/amd64-freetype-2.12.1.tar.xz
    
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/freetype/2.12.1/amd64-freetype-2.12.1-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-freetype-2.12.1.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libfreetype.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
