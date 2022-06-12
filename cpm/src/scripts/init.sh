#!/bin/bash
CPM_CALL_DIR=`pwd -P`
SCRIPT_DIR=`cd $(dirname ${BASH_SOURCE:-$0}); pwd`

REPLACEMENT_TXT=replacement_path_for_cpm_archive.txt
if [ ! -e $SCRIPT_DIR/$REPLACEMENT_TXT ]; then
    # REPLACEMENT_TXT does not exist. And there is no path to replace.
    exit 0
fi

SRC_PATH=`cat $SCRIPT_DIR/replacement_path_for_cpm_archive.txt | tr -d '\r' | tr -d '\n'`
DST_PATH=$SCRIPT_DIR

cd $SCRIPT_DIR
find . -type f -name '*.la' -print0 | xargs -0 sed -i 's!'$SRC_PATH'!'$DST_PATH'!g' > /dev/null 2>&1
find . -type f -name '*.pc' -print0 | xargs -0 sed -i 's!'$SRC_PATH'!'$DST_PATH'!g' > /dev/null 2>&1
echo $DST_PATH > 'replacement_path_for_cpm_archive.txt'
cd $CPM_CALL_DIR
