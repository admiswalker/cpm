#!/bin/bash

CALL_DIR=`pwd -P`

export CACHE_DIR=$CALL_DIR/'env_cpm/cache'
export BUILD_DIR=$CALL_DIR/'env_cpm/build'
export INST_PATH=$CALL_DIR/'env_cpm/local'

sh ./cpm/packages/baseArchive/tag:amd64_gcc-8.4.0/install.sh

