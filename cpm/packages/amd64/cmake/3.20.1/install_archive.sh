#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install cmake/3.20.1 ------------------------------------------------'

mkdir -p $INST_PATH

fName='amd64-cmake-3.20.1.tar.xz'
fName_base=${fName%.*.*} # amd64-cmake-3.20.1

CACHE_BASE=$CACHE_DIR/archive/$fName_base

# installation
if [ ! -e $INST_PATH/lib/libgtest_main.a ]; then
    tar -Jxf $CACHE_BASE/$fName -C $INST_PATH # tar.xz
fi

#    '--------------------------------------------------------------------------------'
echo '-------------------------------------------------- end: install cmake/3.20.1 ---'

