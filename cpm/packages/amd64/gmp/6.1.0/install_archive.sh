#!/bin/bash

# Usage
#   - Set values of `CACHE_DIR`, `BUILD_DIR` and `INST_PATH` using `export` before call this script.

source ./cpm/init_path_and_dir.sh


#    '--------------------------------------------------------------------------------'
echo '--- begin: install gmp/6.1.0 ---------------------------------------------------'

fName='amd64-gmp-6.1.0.tar.xz'
fName_base=${fName%.*.*}  # <architecture>-<libName>-<version>
tmp=${fName%-*}           # <architecture>-<libName>
arcName=${tmp%-*}         # <architecture>
libName=${tmp#*-}         # <libName>
verStr=${fName_base#*-*-} # <version>

# installation
if [ ! -e $CPM_INST_PATH/lib/lib$libName.a ]; then
    tar -Jxf $CPM_CACHE_DIR/$fName -C $CPM_INST_WDIR # tar.xz
fi

#    '--------------------------------------------------------------------------------'
echo '----------------------------------------------------- end: install gmp/6.1.0 ---'
