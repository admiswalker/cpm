#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

CALL_DIR=`pwd -P`
INST_PATH=$CALL_DIR/$INST_PATH # When using Docker, the absolute path is determined at run time.
mkdir -p $INST_PATH


#    '--------------------------------------------------------------------------------'
echo '--- begin: install baseArchive/gcc-8.4.0 ---------------------------------------'

fName='amd64-gcc-8.4.0.tar.xz'
fName_base=${fName%.*.*} # amd64-gcc-8.4.0

# installation
if [ ! -e $INST_PATH/bin/gcc ]; then
    tar -Jxf $CACHE_DIR/$fName -C $INST_PATH
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------- end: install baseArchive/gcc-8.4.0 ---'

