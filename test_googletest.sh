#!/bin/bash

source ./set_env.sh

CALL_DIR=`pwd -P`

export CACHE_DIR=$CALL_DIR/'env_cpm/cache'
export BUILD_DIR=$CALL_DIR/'env_cpm/build'
export INST_PATH=$CALL_DIR/'env_cpm/local'

sh ./cpm/packages/googletest/install_v1.11.0.sh

