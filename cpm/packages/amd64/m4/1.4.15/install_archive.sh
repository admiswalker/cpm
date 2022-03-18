#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: install m4/1.4.15 ---------------------------------------------------'

fName='amd64-m4-1.4.15.tar.xz'
fName_base=${fName%.*.*} # amd64-m4-1.4.15

# installation
if [ ! -e $INST_PATH/bin/m4 ]; then
    tar -Jxf $CACHE_DIR/$fName -C $INST_PATH # tar.xz
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install m4/1.4.15 ---'
