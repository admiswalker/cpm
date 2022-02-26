#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR` using `export` before call this script.

#    '--------------------------------------------------------------------------------'
echo '--- begin: install baseArchive/amd64_gcc-8.4.0 ---------------------------------'

mkdir -p $INST_PATH

libName='gcc-8.4.0'
fName='amd64_gcc-8.4.0.tar.xz'

# installation
if [ ! -e $INST_PATH/bin/gcc ]; then
    tar -Jxf $CACHE_DIR/$libName/$fName -C $INST_PATH
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------- end: install baseArchive/amd64_gcc-8.4.0 ---'

