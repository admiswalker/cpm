#!/bin/bash
CPM_CALL_DIR=`pwd -P`
SCRIPT_DIR=`cd $(dirname ${0}) && pwd`

SRC_PATH=`cat $SCRIPT_DIR/replacement_path_for_cpm_archive.txt | tr -d '\r' | tr -d '\n'`
DST_PATH=$SCRIPT_DIR

cd $SCRIPT_DIR
find . -type f -name '*.la' -print0 | xargs -0 sed -i 's!'$SRC_PATH'!'$DST_PATH'!g'
echo $DST_PATH > 'replacement_path_for_cpm_archive.txt'
cd $CPM_CALL_DIR
