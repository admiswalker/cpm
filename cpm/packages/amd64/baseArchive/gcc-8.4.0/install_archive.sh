#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install baseArchive/gcc-8.4.0 ---------------------------------------'

mkdir -p $INST_PATH

fName='amd64-gcc-8.4.0.tar.xz'
fName_base=${fName%.*.*} # amd64-gcc-8.4.0

CACHE_BASE=$CACHE_DIR/archive/$fName_base

# installation
if [ ! -e $INST_PATH/bin/gcc ]; then
    tar -Jxf $CACHE_BASE/$fName -C $INST_PATH
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------- end: install baseArchive/gcc-8.4.0 ---'

