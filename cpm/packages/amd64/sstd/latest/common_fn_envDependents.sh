#!/bin/bash


cfn_set_archive_URL(){
    pass;
    #URL=
    #URL00=
    #URL01=

    #URL_hash=
}
cfn_set_archive_fName(){
    pass;
    #fName=
}
cfn_isInstalled(){
    if [ -e $CPM_INST_PATH/lib/libsstd.a ]; then
        echo 'true'
    else
        echo 'false'
    fi
}
