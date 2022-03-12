#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
INST_PATH=$CALL_DIR/$INST_PATH; mkdir -p $INST_PATH # When using Docker, the absolute path is determined at run time.


#    '--------------------------------------------------------------------------------'
echo '--- begin: install cmake/3.20.1 ------------------------------------------------'

fName='amd64-cmake-3.20.1.tar.xz'
fName_base=${fName%.*.*} # amd64-cmake-3.20.1

# installation
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    tar -Jxf $CACHE_DIR/$fName -C $INST_PATH # tar.xz
fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------------- end: install cmake/3.20.1 ---'

