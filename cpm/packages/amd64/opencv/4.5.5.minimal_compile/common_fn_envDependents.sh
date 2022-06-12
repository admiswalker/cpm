#!/bin/bash


cfn_set_archive_URL(){
    URL=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/opencv/4.5.5.minimal_compile/amd64-opencv-4.5.5.minimal_compile.tar.xz
    URL_hash=https://github.com/admiswalker/cpm_archive/raw/main/archive/amd64/opencv/4.5.5.minimal_compile/amd64-opencv-4.5.5.minimal_compile-sha256sum.txt
}
cfn_set_archive_fName(){
    fName=amd64-opencv-4.5.5.minimal_compile.tar.xz
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libopencv_aruco.so ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
